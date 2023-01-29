/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:27:16 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 10:49:25 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
void	ft_lstadd_back(t_list **lst, t_list *ne)
{
	t_list	*last;
	if (lst)
	{
		// printf("got here: %p\n",lst);
		if (*lst == NULL)
			*lst = ne;
		else
		{
			last = ft_lstlast(*lst);
			last->next = ne;
		}
	}
}
