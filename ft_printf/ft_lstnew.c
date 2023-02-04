/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:41:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/04 22:24:24 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *key, char *value, int index, int position)
{
	t_list	*node;

	node = malloc (sizeof(t_list));
	if (node)
	{
		node->key = key;
		node->value = value;
		node->index = index;
		node->position = position;
		node->next = NULL;
	}	
	return (node);
}
