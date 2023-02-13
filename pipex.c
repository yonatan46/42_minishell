/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:21:08 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 20:06:35 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_check_builtin: check if the command is one of the built-in
 * @cmd: the command to check
*/
int	ft_check_builtin(char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
		return (1);
	else if (strcmp(cmd, "echo") == 0)
		return (2);
	else if (strcmp(cmd, "cd") == 0)
		return (3);
	else if (strcmp(cmd, "pwd") == 0)
		return (4);
	else if (strcmp(cmd, "env") == 0)
		return (5);
	else if (strcmp(cmd, "export") == 0)
		return (6);
	else if (strcmp(cmd, "unset") == 0)
		return (7);
	return (0);
}

/**
 * close all pipes
 * @proc: struct that have all the variables i use
*/
void	close_pipes(t_data *proc)
{
	int	x;

	x = -1;
	while (++x < proc->total_pipe)
	{
		close(proc->fd[x][0]);
		close(proc->fd[x][1]);
	}
}

/**
 * pipex_two_cmd: execute and return err_code for two cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int	pipex_two_cmd(t_pipe *av, t_data *proc, char **envp)
{
	signal(SIGINT, SIG_IGN);
	proc->pid1 = first_process(proc, av, envp);
	proc->pid2 = last_process(proc, av, envp);
	close_pipes(proc);
	waitpid(proc->pid2, &proc->err_no, 0);
	waitpid(proc->pid1, 0, 0);
	signal(SIGINT, handler_signal);
	if (WIFEXITED(proc->err_no))
		return (WEXITSTATUS(proc->err_no));
	else if (WIFSIGNALED(proc->err_no))
		return (WTERMSIG(proc->err_no) + 128);
	return (0);
}

/**
 * pipex_three_cmd: execute and return err_code for two cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int	pipex_three_cmd(t_pipe *av, t_data *proc, char **envp)
{
	int x = 0;
	proc->counter = 0;
	signal(SIGINT, SIG_IGN);
	first_process(proc, av, envp);
	while (proc->counter < proc->middle_cmd)
	{
		middl_process(proc, av, envp, proc->counter + 1);
		proc->counter++;
	}
	proc->pid2 = last_process(proc, av, envp);
	close_pipes(proc);
	proc->counter = -1;
	waitpid(proc->pid2, &proc->err_no, 0);
	while (x < (av->cmd_len - 1))
	{
		waitpid(-1, 0, 0);
		x++;
	}
	if (WIFEXITED(proc->err_no))
		return (WEXITSTATUS(proc->err_no));
	else if (WIFSIGNALED(proc->err_no))
		return (WTERMSIG(proc->err_no) + 128);
	return (0);
}

/**
 * pipex: where the main execution is happening, 
 * it will execute one two and three cmds
 * @av: a structure that contains the whole variables
 * @ac: number of commands
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int	pipex(int ac, t_pipe *f_pipe, t_data *proc_inp)
{
	t_data	proc;
	int		cmd_len;
	int		counter;
	char 	**envp;
	int		ret;

	ret = 0;
	proc = *proc_inp;
	envp = linked_to_array(*proc.head);
	cmd_len = ac;
	proc.ac = ac;
	proc.middle_cmd = cmd_len - 2;
	proc.total_pipe = cmd_len - 1;
	proc.counter = 0;
	counter = -1;
	if (ac > 1)
		while (++counter < cmd_len - 1)
			pipe(proc.fd[counter]);
	if (ac == 1)
		ret = pipex_one_cmd(f_pipe, &proc, envp);
	else if (ac == 2)
		ret = pipex_two_cmd(f_pipe, &proc, envp);
	else if (ac > 2)
		ret = pipex_three_cmd(f_pipe, &proc, envp);
	else
		printf("Error : no command input\n");
	if(envp)
		free_func(envp);
	return (ret);
}
