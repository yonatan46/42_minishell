/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:25 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/04 22:24:24 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * search: scan the environment variable for the PATH fro 2d array
 * @envp: the environment variable
*/
int	search(char **envp)
{
	int	x;

	x = -1;
	while (envp[++x])
		if (ft_strnstr(envp[x], "PATH=", 5))
			return (1);
	return (0);
}

/**
 * search_env_linked: search the environemnt variable for PATH 
 * but now its linked list
 * @head: the head of the linked list which have env
*/
int	search_env_linked(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strnstr(tmp->key, "PATH", 4))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
