/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linkedlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:54:06 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/01 14:40:03 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * sort_list: is a function that sort linked list
 * @head: the head of linked lists
*/

void	sort_list(t_list *head)
{
	t_list	*current;
	t_list	*compare;
	char	*temp_content;
	char	*temp_value;

	current = head;
	while (current->next != NULL)
	{
		compare = current->next;
		while (compare != NULL)
		{
			if (strcmp(current->content, compare->content) > 0)
			{
				temp_content = current->content;
				temp_value = current->value;
				current->content = compare->content;
				current->value = compare->value;
				compare->content = temp_content;
				compare->value = temp_value;
			}
			compare = compare->next;
		}
		current = current->next;
	}
}

/**
 * remove_element: is a function that removes an element at position of index
 * form the linked list
 * @head: the linked list which contains the env
 * @index: index of list to be removed from the linked list
*/
void	remove_element(t_list **head, int index)
{
	t_list	*current;
	t_list	*prev;
	int x;
	x = 0;

	current = *head;
	prev = NULL;
	if (index == 0)
	{
		*head = current->next;
		free(current);
	}
	else
	{
		while (current != NULL)
		{
			if (current->index == index)
			{
				// printf("index=|%d| %s\n", current->index, current->content);
				prev->next = current->next;
				free(current);
				break ;
			}
			prev = current;
			current = current->next;
		}
	}
	prev = *head;
	while (prev)
	{
		prev->index = x++;
		prev = prev->next;
	}
}


/**
 * linked_to_array: is a function that converts
 * @head: the head of the linked list
*/
char	**linked_to_array(t_list *head)
{
	t_list	*tmp;
	char	**copy_env;
	int		len;
	int		x;

	len = ft_lstsize(head);
	tmp = head;
	copy_env = malloc(sizeof(char *) * (len + 1));
	x = 0;
	while (tmp)
	{
		copy_env[x] = ft_strjoin(tmp->content, tmp->value);
		tmp = tmp->next;
		x++;
	}
	copy_env[x] = NULL;
	return (copy_env);
}


/**
 * 
*/

char *ft_getenv(t_list *head, char *str)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, str, ft_strlen(tmp->content) - 1) == 0)
			return(tmp->value);
		tmp = tmp->next;		
	}
	return(NULL);
}