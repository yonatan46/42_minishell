/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:17:59 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 09:51:56 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ultimate_free: is a function that free mostly everything 
 * that we have
 * @data: the structure containing infor about the whole execution
 * @pipe: an array of structs containing info of all the execution
*/
void	ultimate_free(t_data *data, t_pipe *pipe)
{
	int	x;

	x = 0;
	while (x < pipe->cmd_len)
	{
		if (pipe[x].arg)
			free_func(pipe[x].arg);
		if (pipe[x].cmd)
			free(pipe[x].cmd);
		free_func(pipe[x].f_cmd);
		x++;
	}
	free_list(*data->head);
	free(data->head);
	free(pipe);
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

/**
 * free_redirection: a function to free all the redirections we have
 * @pipe: a structure that hold the whole commands and args
*/
void	free_redirection(t_pipe *pipe)
{
	int	x;
	int	i;

	x = 0;
	while (x < pipe->cmd_len)
	{
		i = 0;
		while (i < pipe[x].red_len)
		{
			free(pipe[x].red[i]->red_name);
			free(pipe[x].red[i]->red_sign);
			free(pipe[x].red[i]);
			i++;
		}
		free(pipe[x].red);
		x++;
	}
}

void	comb_free(t_pipe *pipe, t_data *proc)
{
	free_func(proc->envp);
	free_redirection(pipe);
	ultimate_free(proc, pipe);
}

void	simple_free(char *str)
{
	if (str)
		free(str);
}
