/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_cmd_proccess.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:03:36 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/05 13:17:23 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * check_built_ins_and_exexute_one_cmd: check if the 
 * command is one of the built ins 
 * and execute that but now its for one command only
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables 
*/
void	check_built_ins_and_exexute_one_cmd(t_data *proc, \
t_pipe *av, char **envp)
{
	(void)envp;
	if (proc->check == 1)
		ft_exit(av);
	else if (proc->check == 2)
		ft_echo(av);
	else if (proc->check == 3)
		ft_cd(av, proc);
	else if (proc->check == 4)
		ft_pwd();
	else if (proc->check == 5)
		ft_env_print_linked(proc);
	else if (proc->check == 6)
		ft_export_print_linked(av, proc);
	else if (proc->check == 7)
		ft_unset(av, proc);
	exit(1);
}

/**
 * one_cmd_process: a function that execute one command
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables 
*/
void	one_cmd_process(t_data *proc, t_pipe *av, char **envp)
{
	(void)envp;
	proc->id = fork();
	if (proc->id < 0)
		terminate("fork");
	if (proc->id == 0)
	{
		if (av->red_len > 0)
			red_one_cmd(av);
		proc->check = ft_check_builtin(av->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute_one_cmd(proc, av, envp);
		if (av->cmd && parsing(proc, envp, av->cmd))
		{
			execve(parsing(proc, envp, av->cmd), \
			av->arg, envp);
			free_func_one_cmd(av);
		}
		else
			cmd_not_found(av);
	}
}

/**
 * pipex_one_cmd: execute and return err_code for one cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int	pipex_one_cmd(t_pipe *av, t_data *proc, char **envp)
{
	if (strcmp(av[0].cmd, "cd") == 0)
		return (ft_cd(&av[0], proc));
	else if (strcmp(av[0].cmd, "exit") == 0)
	{
		ft_exit(&av[0]);
		return (1);
	}
	else if (strcmp(av[0].cmd, "unset") == 0)
		return (ft_unset(&av[0], proc));
	else if (strcmp(av[0].cmd, "export") == 0)
		return (ft_export_print_linked(&av[0], proc));
	else
	{
		one_cmd_process(proc, &av[0], envp);
		waitpid(-1, &proc->err_no, 0);
		if (WIFEXITED(proc->err_no))
			return (WEXITSTATUS(proc->err_no));
		else if (WIFSIGNALED(proc->err_no))
			return (WTERMSIG(proc->err_no));
	}
	return (0);
}
