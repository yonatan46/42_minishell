/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:45:06 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 09:21:25 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_cd_util: check if current pwd exits,, then change dir 
 * and replace env, accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
static int	ft_cd_util(t_pipe *pipe, char *pwd, t_data *proc)
{
	char	*tmp;

	if (chdir(pipe->arg[1]) == 0)
	{
		if (pwd)
		{
			tmp = ft_strjoin("OLDPWD=", pwd);
			chek_exp_a_rplc(*proc->head, tmp);
			free(tmp);
		}
		pwd = getcwd(proc->pwd, 1024);
		tmp = ft_strjoin("PWD=", pwd);
		if (pwd)
			return (free(tmp), chek_exp_a_rplc(*proc->head, tmp));
		ft_putstr_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory\n", 2);
		return (1);
	}
	else
	{
		write(1, pipe->arg[1], ft_strlen(pipe->arg[1]));
		perror(" ");
		return (1);
	}
	return (0);
}

/**
 * ft_cd_util_3: check if home is set and change the dir to home
 * and update oldpwd and pwd accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
static	int	ft_cd_util_3(char *pwd, t_data *proc)
{
	char	*tmp;

	if (pwd)
	{
		tmp = ft_strjoin("OLDPWD=", pwd);
		chek_exp_a_rplc(*proc->head, tmp);
		if (tmp)
			free(tmp);
	}
	pwd = getcwd(proc->pwd, 1024);
	if (pwd)
	{
		tmp = ft_strjoin("PWD=", pwd);
		return (free(tmp), chek_exp_a_rplc(*proc->head, tmp));
	}
	return (1);
}

/**
 * ft_cd_util_2: check if home is set and change the dir to home
 * and update oldpwd and pwd accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
static	int	ft_cd_util_2(char *pwd, t_data *proc)
{
	char	*tmp;

	if (chdir(ft_getenv(*proc->head, "HOME")) == 0)
		return (ft_cd_util_3(pwd, proc));
	else
	{
		tmp = ft_getenv(*proc->head, "HOME");
		if (tmp == NULL)
			ft_putstr_fd("cd: HOME not set\n", 2);
		else
		{
			write(2, tmp, ft_strlen(tmp));
			perror(" ");
		}
		return (free(tmp), 1);
	}
	return (0);
}

/**
 * ft_cd: changed  the current working directory
 * @pipe: the struct that contains the whold command and instructions
*/
int	ft_cd(t_pipe *pipe, t_data *proc)
{
	char	*pwd;

	pwd = getcwd(proc->pwd, 1024);
	proc->x = 0;
	if (pipe->arg[1])
	{
		proc->x = ft_cd_util(pipe, pwd, proc);
		if (pipe->cmd_len > 1)
		{
			free_redirection(pipe);
			free_func(proc->envp);
			ultimate_free(proc, pipe);
		}
	}
	else if (pipe->arg[1] == NULL)
	{
		proc->x = ft_cd_util_2(pwd, proc);
		if (pipe->cmd_len > 1)
		{
			free_func(proc->envp);
			free_redirection(pipe);
			ultimate_free(proc, pipe);
		}
	}
	return (proc->x);
}
