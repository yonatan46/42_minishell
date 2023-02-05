/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:27:16 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/05 13:23:48 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *ne)
{
	t_list	*last;

	if (lst)
	{
		if (*lst == NULL)
			*lst = ne;
		else
		{
			last = ft_lstlast(*lst);
			last->next = ne;
		}
	}
}
