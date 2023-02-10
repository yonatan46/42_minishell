/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:45:06 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/10 12:36:46 by yonamog2         ###   ########.fr       */
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
		{
			int val = chek_exp_a_rplc(*proc->head, tmp);
			free(tmp);
			return (val);
		}
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
 * ft_cd_util_2: check if home is set and change the dir to home
 * and update oldpwd and pwd accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
static int	ft_cd_util_2(char *pwd, t_data *proc)
{
	char	*tmp;
	int		ret;
	if (chdir(ft_getenv(*proc->head, "HOME")) == 0)
	{
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
			ret = chek_exp_a_rplc(*proc->head, tmp);
			if (tmp)
				free(tmp);
			return (ret);
		}
		return (1);
	}
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
		if (tmp)
			free(tmp);
		return (1);
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
	int		ret;

	pwd = getcwd(proc->pwd, 1024);
	ret = 0;
	if (pipe->arg[1])
	{
		ret = ft_cd_util(pipe, pwd, proc);
		if(pipe->cmd_len > 1)
		{
			free_list(*proc->head);
			free(proc->head);
			free_func(proc->envp);
			free_redirection(pipe);
			int x = 0;
			while (x < pipe->cmd_len)
			{
				free(pipe[x].cmd);
				free_func(pipe[x].arg);
				free_func(pipe[x].f_cmd);
				x++;
			}
			free(pipe);
		}
	}
	else if (pipe->arg[1] == NULL)
	{
		ret = ft_cd_util_2(pwd, proc);
		// free_list(*proc->head);
		// free(proc->head);
		// free_func(pipe->arg);
		// free(pipe);

		if(pipe->cmd_len > 1)
		{
			free_list(*proc->head);
			free(proc->head);
			free_func(proc->envp);
			free_redirection(pipe);
			int x = 0;
			while (x < pipe->cmd_len)
			{
				free(pipe[x].cmd);
				free_func(pipe[x].arg);
				free_func(pipe[x].f_cmd);
				x++;
			}
			free(pipe);
		}
	}
	return (ret);
}
