/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:21:08 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/02 11:20:23 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * free_short: frr one string and 2d array
 * @path: the string to be freed
 * @path_split: the 2d array to be freed
*/
void	free_short(char *path, char **path_split)
{
	free(path);
	free_func(path_split);
}

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
 * parsing_middle: parsing the middle command
 * @proc: the structure containing all info
 * @envp: the environment variable
 * @s: the command string
*/
char	*parsing_middle(t_data *proc, char **envp, char *s)
{
	proc->x = 0;
	if (search(envp) == 0)
		return (NULL);
	if (ft_strnstr(s, "/", ft_strlen(s)))
		return (s);
	while (!ft_strnstr(envp[proc->x], "PATH", 4))
		proc->x++;
	proc->path_split = ft_split(envp[proc->x] + 5, ':');
	proc->x = -1;
	while (proc->path_split[++proc->x] && (search(envp) == 1))
	{
		proc->path = ft_strjoin(proc->path_split[proc->x], "/");
		proc->result = ft_strjoin(proc->path, s);
		if (access(proc->result, 0) == 0)
		{
			free_short(proc->path, proc->path_split);
			return (proc->result);
		}
		if (proc->path)
			free(proc->path);
		free(proc->result);
	}
	return (free_short(NULL, proc->path_split), NULL);
}

/**
 * pars and check validity of command
*/
char	*parsing(t_data *proc, char **envp, char *s)
{
	(void)envp;
	proc->x = -1;
	proc->tmp_list = *proc->head;
	if (ft_strnstr(s, "/", ft_strlen(s)))
		return (s);
	if (search(envp) == 0)
		return (NULL);
	while (envp[++proc->x])
	{
		if (ft_strncmp(envp[proc->x], "PATH=", 5) == 0)
			break;
	}
	proc->tmp_list = proc->tmp_list->next;
	proc->path_split = ft_split(envp[proc->x] + 5, ':');
	proc->x = -1;
	while (proc->path_split[++proc->x] && (search(envp) == 1))
	{
		proc->path = ft_strjoin(proc->path_split[proc->x], "/");
		proc->result = ft_strjoin(proc->path, s);
		if (access(proc->result, 0) == 0)
			return (free_short(proc->path, proc->path_split), proc->result);
		if (proc->path)
			free(proc->path);
		free(proc->result);
	}
	return (free_short(NULL, proc->path_split), NULL);
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
		if (av->red_len > 0)
			red_first_proc(av, &proc->flag);
		if (proc->flag == 0)
			dup2(proc->fd[0][1], STDOUT_FILENO);
		close_pipes(proc);
		proc->check = ft_check_builtin(av->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		if (av->cmd && parsing(proc, envp, av->cmd))
		{
			execve(parsing(proc, envp, av->cmd), av->arg, envp);
			free_func(av->arg);
		}
		else
			cmd_not_found(av);
	}
	return (proc->id);
}

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
		ft_exit(av, proc);
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
		cmd_not_found(av);
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
		// printf("middle pipe num %d\n", proc->counter);
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
		if (av->red_len > 0)
			red_last_proc(av, &proc->flag);
		if (proc->flag == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		proc->check = ft_check_builtin(av->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		else if (av->cmd && parsing(proc, envp, av->cmd))
		{
			execve(parsing(proc, envp, av->cmd), av->arg, envp);
			free_func(av->arg);
		}
		else
			cmd_not_found(av);
	}
	return (proc->id1);
}

void print_export(t_data *proc)
{
	t_list *head;
	head = *proc->head;
	while (head)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
}
/**
 * pipex_one_cmd: execute and return err_code for one cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int pipex_one_cmd(t_pipe *av, t_data *proc, char **envp)
{
	if (strcmp(av[0].cmd, "cd") == 0)
		return(ft_cd(&av[0], proc));
	else if (strcmp(av[0].cmd, "exit") == 0)
	{
		write(2, "exit\n", 5);
		ft_exit(&av[0], proc);
		return (1);
	}
	else if (strcmp(av[0].cmd, "unset") == 0)
		return(ft_unset(&av[0], proc));
	else if (strcmp(av[0].cmd, "export") == 0)
		return(ft_export_print_linked(&av[0], proc));
	else
	{
		// signal(SIGINT, SIG_DFL);
		one_cmd_process(proc, &av[0], envp);
		waitpid(-1, &proc->err_no, 0);
		if (WIFEXITED(proc->err_no))
			return (WEXITSTATUS(proc->err_no));
		else if (WIFSIGNALED(proc->err_no))
			return (WTERMSIG(proc->err_no));
	}
	return (0);
}

/**
 * pipex_two_cmd: execute and return err_code for two cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int pipex_two_cmd(t_pipe *av, t_data *proc, char **envp)
{
	proc->pid1 = first_process(proc, &av[0], envp);
	proc->pid2 = last_process(proc, &av[1], envp);
	close_pipes(proc);
	waitpid(proc->pid1, 0, 0);
	waitpid(proc->pid2, &proc->err_no, 0);
	if (WIFEXITED(proc->err_no))
		return (WEXITSTATUS(proc->err_no));
	return (0);
}

/**
 * pipex_three_cmd: execute and return err_code for two cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int pipex_three_cmd(t_pipe *av, t_data *proc, char **envp)
{
	proc->counter = 0;
	first_process(proc, &av[0], envp);
	while (proc->counter < proc->middle_cmd)
	{
		middl_process(proc, &av[proc->counter + 1], envp);
		proc->counter++;
	}
	proc->pid2 = last_process(proc, &av[proc->ac - 1], envp);
	close_pipes(proc);
	proc->counter = -1;
	waitpid(proc->pid2, &proc->err_no, 0);
	while (waitpid(-1, 0, 0) != -1)
		;
	if (WIFEXITED(proc->err_no))
		return (WEXITSTATUS(proc->err_no));
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

	proc = *proc_inp;
	cmd_len = ac;
	proc.ac = ac;
	proc.middle_cmd = cmd_len - 2;
	proc.total_pipe = cmd_len - 1;
	proc.counter = 0;
	counter = -1;
	if (ac > 1)
		while (++counter < cmd_len - 1)
			pipe(proc.fd[counter]);
	// if (f_pipe->arg[0] == NULL)
	// {
	// 	int x = 0;
	// 	while (x < f_pipe->cmd_len)
	// 	{
	// 		f_pipe[x].arg = malloc(sizeof(char *) * 2);
	// 		f_pipe[x].arg[0] = ft_strdup("asjsabdjhbs");
	// 		f_pipe[x].arg[1] = NULL;
	// 		x++;
	// 	}
	// }
	if (ac == 1)
		return (pipex_one_cmd(f_pipe, &proc, linked_to_array(*proc.head)));
	else if (ac == 2)
		return (pipex_two_cmd(f_pipe, &proc, linked_to_array(*proc.head)));
	else if (ac > 2)
		return (pipex_three_cmd(f_pipe, &proc, linked_to_array(*proc.head)));
	else
		printf("Error : no command input\n");
	return (0);
}
