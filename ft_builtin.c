/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:52:10 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/04 21:34:49 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_print_echo: print arguments to the terminal
 * @pipe: the structure containint the commands, redirections and args
 * @x: the indexing for the ags
*/
void	ft_print_echo(t_pipe *pipe, int x)
{
	while (pipe->arg[++x])
	{
		if (pipe->arg[x + 1] == NULL)
			printf("%s", pipe->arg[x]);
		else
			printf("%s ", pipe->arg[x]);
	}
}

/**
 * ft_echo: will just take a string and print it
 * @pipe: a structure that hold the whole commands and args
*/
void	ft_echo(t_pipe *pipe)
{
	int	x;

	x = 0;
	if (pipe->arg[1] == NULL)
		printf("\n");
	else if (strcmp(pipe->arg[1], "-n") == 0)
	{
		x++;
		ft_print_echo(pipe, x);
	}
	else
	{
		ft_print_echo(pipe, x);
		printf("\n");
	}
	exit(0);
}

/**
 * ft_pwd: will print the current directory
*/
void	ft_pwd(void)
{
	char	res[1024];
	char	*pwd;

	pwd = getcwd(res, 1024);
	if (!pwd)
	{
		ft_putstr_fd("Error: sorry dir is deleted or incorrect!\n", 2);
		exit(1);
	}
	printf("%s\n", pwd);
	exit(0);
}

/**
 * scan_exit_codes: just scan the sargs of exit,
 * @pipe: the structure containin the whole command, args and redirections
*/
int	scan_exit_codes(t_pipe *pipe)
{
	int	j;

	j = -1;
	while (pipe->arg[1][++j])
	{
		if (j == 0 && (pipe->arg[1][j] == '+' || pipe->arg[1][j] == '-'))
			continue ;
		if (ft_isdigit(pipe->arg[1][j]) == 0)
			return (1);
	}
	return (0);
}

/**
 * ft_exit: will print the current directory
 * @pipe: the struct that contains the whold command and instructions
*/
void	ft_exit(t_pipe *pipe)
{
	int		err_code;

	err_code = 0;
	if (pipe->arg[1] == NULL)
		exit(g_err_code);
	if (pipe->arg[2])
	{
		write(2, pipe->cmd, ft_strlen(pipe->cmd));
		ft_putstr_fd(": too many arguments\n", 2);
		return ;
	}
	if (scan_exit_codes(pipe) == 1)
	{
		write(2, pipe->cmd, ft_strlen(pipe->cmd));
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (pipe->arg[1])
		err_code = (unsigned char)ft_atoi(pipe->arg[1]);
	exit(err_code);
}

/**
 * ft_cd_util: check if current pwd exits,, then change dir 
 * and replace env, accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
int	ft_cd_util(t_pipe *pipe, char *pwd, t_data *proc)
{
	if (chdir(pipe->arg[1]) == 0)
	{
		if (pwd)
			chek_exp_a_rplc(*proc->head, ft_strjoin("OLDPWD=", pwd));
		pwd = getcwd(proc->pwd, 1024);
		if (pwd)
			return (chek_exp_a_rplc(*proc->head, ft_strjoin("PWD=", pwd)));
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
int	ft_cd_util_2(char *pwd, t_data *proc)
{
	if (chdir(ft_getenv(*proc->head, "HOME")) == 0)
	{
		if (pwd)
			chek_exp_a_rplc(*proc->head, ft_strjoin("OLDPWD=", pwd));
		pwd = getcwd(proc->pwd, 1024);
		if (pwd)
			return (chek_exp_a_rplc(*proc->head, ft_strjoin("PWD=", pwd)));
		return (1);
	}
	else
	{
		if (ft_getenv(*proc->head, "HOME") == NULL)
			ft_putstr_fd("cd: HOME not set\n", 2);
		else
		{
			write(2, ft_getenv(*proc->head, "HOME"), \
			ft_strlen(ft_getenv(*proc->head, "HOME")));
			perror(" ");
		}
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

	pwd = getcwd(proc->pwd, 1024);
	if (pipe->arg[1])
		return (ft_cd_util(pipe, pwd, proc));
	else if (pipe->arg[1] == NULL)
		return (ft_cd_util_2(pwd, proc));
	return (0);
}
