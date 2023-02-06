/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_more_cmd_proccess.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:07:19 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/06 21:08:27 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * check_built_ins_and_exexute: check if the command is one of the built ins 
 * and execute
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables 
*/
void	check_built_ins_and_exexute(t_data *proc, t_pipe *av, char **envp)
{
	(void)envp;
	if (proc->check == 1)
		ft_exit(av);
	else if (proc->check == 2)
		ft_echo(av, proc, envp);
	else if (proc->check == 3)
		ft_cd(av, proc);
	else if (proc->check == 4)
		ft_pwd(proc, av, envp);
	else if (proc->check == 5)
		ft_env_print_linked(proc);
	else if (proc->check == 6)
		ft_export_print_linked(av, proc);
	else if (proc->check == 7)
		ft_unset(av, proc);
	exit(0);
}

/**
 * first_process: executing the first command
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables 
*/
int	first_process(t_data *proc, t_pipe *av, char **envp)
{
	proc->flag = 0;
	proc->id = fork();
	if (proc->id < 0)
		terminate("fork");
	if (proc->id == 0)
	{
		signal(SIGINT, handler_signal);
		if (av[0].red_len > 0)
			red_first_proc(&av[0], &proc->flag);
		if (proc->flag == 0)
			dup2(proc->fd[0][1], STDOUT_FILENO);
		close_pipes(proc);
		proc->check = ft_check_builtin(av[0].cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		if (av->cmd && parsing(proc, envp, av[0].cmd))
		{
			execve(parsing(proc, envp, av[0].cmd), av[0].arg, envp);
			free_func(av->arg);
		}
		else
			cmd_not_found(av, proc);
	}
	return (proc->id);
}

/**
 * middle_proc_execute: execution_of proccess
*/
void	middle_proc_execute(t_data *proc, t_pipe *av, char **envp)
{
	(void)av;
	if (av->cmd && parsing_middle(proc, \
		linked_to_array(*proc->head), av->cmd))
	{
		execve(parsing_middle(proc, envp, av->cmd), \
		av->arg, linked_to_array(*proc->head));
		free_func(av->arg);
	}
	else
		cmd_not_found(av, proc);
}

void	middl_process(t_data *proc, t_pipe *av, char **envp)
{
	proc->flag_out = 0;
	proc->flag_in = 0;
	proc->id = fork();
	if (proc->id < 0)
		terminate("fork");
	if (proc->id == 0)
	{
		signal(SIGINT, handler_signal);
		if (av->red_len > 0)
			red_middle(av, &proc->flag_out, &proc->flag_in);
		if (proc->flag_out == 0)
			dup2(proc->fd[proc->counter + 1][1], STDOUT_FILENO);
		if (proc->flag_in == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		proc->res2 = ft_split(av->cmd, ' ');
		proc->check = ft_check_builtin(av->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		middle_proc_execute(proc, av, envp);
	}
}

int	last_process(t_data *proc, t_pipe *av, char **envp)
{
	proc->flag = 0;
	proc->id1 = fork();
	if (proc->id1 < 0)
		terminate("fork");
	if (proc->id1 == 0)
	{
		signal(SIGINT, handler_signal);
		if (av[av->cmd_len - 1].red_len > 0)
			red_last_proc(&av[av->cmd_len - 1], &proc->flag);
		if (proc->flag == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		proc->check = ft_check_builtin(av[0].cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		else if (av[av->cmd_len - 1].cmd && parsing(proc, envp, av[av->cmd_len - 1].cmd))
		{
			execve(parsing(proc, envp, av->cmd), av[av->cmd_len - 1].arg, envp);
			free_func(av->arg);
		}
		else
			cmd_not_found(av, proc);
	}
	return (proc->id1);
}
