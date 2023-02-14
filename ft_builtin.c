/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:52:10 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 20:05:36 by yonamog2         ###   ########.fr       */
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
	int	flag;

	flag = 0;
	while (++x < pipe->arg_len)
	{
		if ((check_nns(pipe->arg[x]) == 0 && flag == 0) || !pipe->arg[x])
			continue ;
		if (pipe->arg[x + 1] == NULL)
			printf("%s", pipe->arg[x]);
		else
			printf("%s ", pipe->arg[x]);
		flag = 1;
	}
}

/**
 * ft_echo: will just take a string and print it
 * @pipe: a structure that hold the whole commands and args
*/
void	ft_echo(t_pipe *pipe, t_data *proc, char **envp)
{
	if (pipe[proc->index].arg_len == 1)
	{
		printf("\n");
		free_func(envp);
		free_redirection(pipe);
		ultimate_free(proc, pipe);
	}
	else if (check_nns(pipe[proc->index].arg[1]) == 0)
	{
		ft_print_echo(&pipe[proc->index], 1);
		free_func(envp);
		ultimate_free(proc, pipe);
	}
	else
	{
		ft_print_echo(&pipe[proc->index], 0);
		printf("\n");
		free_redirection(pipe);
		free_func(envp);
		ultimate_free(proc, pipe);
	}
	exit(0);
}

/**
 * ft_pwd: will print the current directory
*/
void	ft_pwd(t_data *data, t_pipe *pipe, char **envp)
{
	char	res[4096];
	char	*pwd;

	pwd = getcwd(res, 4096);
	free_redirection(pipe);
	free_func(envp);
	if (!pwd)
	{
		ft_putstr_fd("Error: sorry dir is deleted or incorrect!\n", 2);
		ultimate_free(data, pipe);
		exit(1);
	}
	printf("%s\n", pwd);
	ultimate_free(data, pipe);
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
void	ft_exit(t_pipe *pipe, t_data *proc)
{
	proc->x = 0;
	if (pipe[proc->index].arg[1] == NULL)
	{
		comb_free(pipe, proc);
		exit(g_err_code);
	}
	if (pipe[proc->index].arg[2])
	{
		write(2, pipe[proc->index].cmd, ft_strlen(pipe[proc->index].cmd));
		ft_putstr_fd(": too many arguments\n", 2);
		return ;
	}
	if (scan_exit_codes(&pipe[proc->index]) == 1)
	{
		write(2, pipe[proc->index].cmd, ft_strlen(pipe[proc->index].cmd));
		ft_putstr_fd(": numeric argument required\n", 2);
		comb_free(pipe, proc);
		exit(255);
	}
	if (pipe[proc->index].arg[1])
		proc->x = (unsigned char)atoi_md(pipe[proc->index].arg[1], pipe, proc);
	comb_free(pipe, proc);
	exit(proc->x);
}
