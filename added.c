/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   added.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:03:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 20:58:37 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * free_func: a function that free 2d array
 * @args: 2d array to be freed
*/
void	free_func(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		if (args[i])
			free(args[i++]);
	if (args)
		free(args);
	args = NULL;
}

/**
 * exit_with_code: a function that exit with the status
*/
void	exit_with_code(t_pipe *av, t_data *proc)
{
	if (av[proc->index].cmd[ft_strlen(av[proc->index].cmd) - 1] == '/')
	{
		ft_putstr_fd(": is a directory\n", 2);
		ultimate_free(proc, av);
		exit(126);
	}
	if (access(av[proc->index].cmd, F_OK) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		ultimate_free(proc, av);
		exit(127);
	}
	else if (access(av[proc->index].cmd, X_OK) == -1)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		ultimate_free(proc, av);
		exit(126);
	}
	else
	{
		ft_putstr_fd(": is a directory\n", 2);
		ultimate_free(proc, av);
		exit(126);
	}
}

/**
 * free_func_one_cmd: a function that free 2d array
 * @args: 2d array to be freed
*/
void	free_func_one_cmd(t_pipe *av, t_data *proc, char **envp)
{
	(void)envp;
	free_func(proc->envp);
	free_redirection(av);
	if (av[proc->index].cmd && av[proc->index].cmd[0] != '\0')
	{
		ft_putstr_fd(av[proc->index].cmd, 2);
		exit_with_code(av, proc);
	}
	ultimate_free(proc, av);
	exit(0);
}

/**
 * terminate: a function that print error 
 *	@m: the string to dispplay before 
*/

void	terminate(char *m, t_data *proc, t_pipe *pipe)
{
	free_func(proc->envp);
	if (access(m, W_OK) == -1 || access(m, R_OK) == -1)
		perror(m);
	else
		perror(m);
	free_redirection(pipe);
	ultimate_free(proc, pipe);
	exit(1);
}

/**
 * cmd_not_found: a function that prints command not found and exit with 127 code
 * @res: a 2d array which contains the string name to be printed
*/
void	cmd_not_found(t_pipe *av, t_data *proc, int counter)
{
	free_func(proc->envp);
	write(2, av[counter].cmd, ft_strlen(av[counter].cmd));
	ft_putstr_fd(": command not found\n", 2);
	free_redirection(av);
	ultimate_free(proc, av);
	exit(127);
}
