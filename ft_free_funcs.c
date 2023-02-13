/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:17:59 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 20:58:25 by yonamog2         ###   ########.fr       */
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
