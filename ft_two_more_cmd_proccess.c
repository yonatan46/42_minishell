/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_more_cmd_proccess.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:07:19 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 19:33:52 by yonamog2         ###   ########.fr       */
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
		ft_exit(av, proc);
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
	char	*tmp;
	int		x;

	proc->index = 0;
	proc->flag = 0;
	proc->envp = envp;
	proc->id = fork();
	if (proc->id < 0)
		terminate("fork", proc, av);
	if (proc->id == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (av[0].red_len > 0)
			red_first_proc(&av[0], &proc->flag, proc);
		if (proc->flag == 0)
			dup2(proc->fd[0][1], STDOUT_FILENO);
		close_pipes(proc);
		if (av[0].cmd == NULL)
		{
			x = 0;
			while (x < av->cmd_len)
			{
				if (av[x].arg)
					free_func(av[x].arg);
				if (av[x].cmd)
					free(av[x].cmd);
				free_func(av[x].f_cmd);
				x++;
			}
			free_redirection(av);
			if (av)
				free(av);
			free_list(*proc->head);
			free(proc->head);
			free_func(proc->envp);
			exit(0);
		}
		proc->check = ft_check_builtin(av[0].cmd);
		if (av[0].cmd && proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		tmp = parsing(proc, envp, av[0].cmd);
		if (av[0].cmd && tmp && av[0].cmd[0])
		{
			execve(tmp, av[0].arg, envp);
			free_func_one_cmd(av, proc, envp);
		}
		else
		{
			if (tmp && tmp[0])
				free(tmp);
			cmd_not_found(av, proc, 0);
		}
	}
	return (proc->id);
}

/**
 * middle_proc_execute: execution_of proccess
*/
void	middle_proc_execute(t_data *proc, t_pipe *av, char **envp, int counter)
{
	char	*tmp;

	tmp = parsing_middle(proc, envp, av[counter].cmd);
	if (av[counter].cmd && tmp && av[counter].cmd[0])
	{
		proc->index = counter;
		execve(tmp, av[counter].arg, envp);
		free_func_one_cmd(av, proc, envp);
	}
	else
	{
		if (tmp && tmp[0])
			free(tmp);
		cmd_not_found(av, proc, counter);
	}
}

void	middl_process(t_data *proc, t_pipe *av, char **envp, int counter)
{
	proc->index = counter;
	proc->flag_out = 0;
	proc->flag_in = 0;
	proc->id = fork();
	if (proc->id < 0)
		terminate("fork", proc, av);
	if (proc->id == 0)
	{
		if (av[counter].red_len > 0)
			red_middle(av, &proc->flag_out, &proc->flag_in, proc);
		if (proc->flag_out == 0)
			dup2(proc->fd[proc->counter + 1][1], STDOUT_FILENO);
		if (proc->flag_in == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		proc->check = ft_check_builtin(av[counter].cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		middle_proc_execute(proc, av, envp, counter);
	}
}

int	last_process(t_data *proc, t_pipe *av, char **envp)
{
	int		x;
	char	*tmp;

	proc->index = av->cmd_len - 1;
	proc->flag = 0;
	proc->id1 = fork();
	if (proc->id1 < 0)
		terminate("fork", proc, av);
	if (proc->id1 == 0)
	{
		if (av[av->cmd_len - 1].red_len > 0)
			red_last_proc(av, &proc->flag, proc);
		if (proc->flag == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		if (av[av->cmd_len - 1].cmd == NULL)
		{
			x = 0;
			while (x < av->cmd_len)
			{
				if (av[x].arg)
					free_func(av[x].arg);
				if (av[x].cmd)
					free(av[x].cmd);
				free_func(av[x].f_cmd);
				x++;
			}
			free_redirection(av);
			if (av)
				free(av);
			free_list(*proc->head);
			free(proc->head);
			free_func(proc->envp);
			exit(0);
		}
		proc->check = ft_check_builtin(av[av->cmd_len - 1].cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		tmp = parsing(proc, envp, av[av->cmd_len - 1].cmd);
		if (av[av->cmd_len - 1].cmd && tmp && av[av->cmd_len - 1].cmd[0])
		{
			execve(tmp, av[av->cmd_len - 1].arg, envp);
			free_func_one_cmd(av, proc, envp);
		}
		else
		{
			if (tmp && tmp[0])
				free(tmp);
			cmd_not_found(av, proc, av->cmd_len - 1);
		}
	}
	return (proc->id1);
}
