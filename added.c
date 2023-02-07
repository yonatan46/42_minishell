/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   added.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:03:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/07 14:29:13 by yonamog2         ###   ########.fr       */
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
	{
		if (args[i])
			free(args[i++]);
	}
	if (args)
		free(args);
}

/**
 * exit_with_code: a function that exit with the status
*/
void	exit_with_code(t_pipe *av, t_data *proc)
{
	if (av->cmd[ft_strlen(av->cmd) - 1] == '/')
	{
		ft_putstr_fd(": is a directory\n", 2);
		free_list(*proc->head);
		free_func(av->arg);
		free(proc->head);
		free(av->cmd);
		free(av);
		close(0);
		close(1);
		close(2);
		exit(126);
	}
	if (access(av->cmd, F_OK) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		free_list(*proc->head);
		free(proc->head);
		free(av->cmd);
		free_func(av->arg);
		free(av);
		close(0);
		close(1);
		close(2);
		exit(127);
	}
	else if (access(av->cmd, X_OK) == -1)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		free_list(*proc->head);
		free(proc->head);
		free(av->cmd);
		free_func(av->arg);
		free(av);
		close(0);
		close(1);
		close(2);
		exit(126);
	}
	else
	{
		ft_putstr_fd(": is a directory\n", 2);
		free_list(*proc->head);
		free(proc->head);
		free_func(av->arg);
		free(av->cmd);
		free(av);
		close(0);
		close(1);
		close(2);
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
	int x = 0;

	while (x < av->cmd_len)
	{
		free_func(av[x].f_cmd);
		x++;
	}
	if (av->cmd[0] != '\0')
	{
		write(1, av->cmd, ft_strlen(av->cmd));
		exit_with_code(av, proc);
	}
	free_list(*proc->head);
	free(proc->head);
	free_func(av->arg);
	free(av->cmd);
	free(av);
	close(0);
	close(1);
	close(2);
	exit(0);
}

/**
 * terminate: a function that print error 
 *	@m: the string to dispplay before 
*/

void	terminate(char *m, t_data *proc, t_pipe *pipe)
{
	if (access(m, W_OK) == -1 || access(m, R_OK) == -1)
		perror(m);
	else
		perror(m);
	int x = 0;
	while (x < pipe->cmd_len)
	{
		free_func(pipe[x].f_cmd);
		x++;
	}
	free_func(proc->envp);
	free_redirection(pipe);
	free_func(pipe->arg);
	free_list(*proc->head);
	free(proc->head);
	free(pipe->cmd);
	free(pipe);
	close(0);
	close(1);
	close(2);
	exit(1);
}

/**
 * cmd_not_found: a function that prints command not found and exit with 127 code
 * @res: a 2d array which contains the string name to be printed
*/
void	cmd_not_found(t_pipe *av, t_data *proc)
{
	write(2, av->cmd, ft_strlen(av->cmd));
	ft_putstr_fd(": command not found\n", 2);
	int x = 0;
	while (x < av->cmd_len)
	{
		free_func(av[x].f_cmd);
		x++;
	}
	// free_func(proc->envp);
	free_func(av->arg);
	free_list(*proc->head);
	free(proc->head);
	free(av->cmd);
	free(av);
	close(2);
	close(1);
	close(0);
	exit(127);
}

/**
 * free_list: function that frees the linked list
 * @head: head of the linked list
*/
void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = next;
	}
	head = NULL;
}
