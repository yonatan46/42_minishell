/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:41:47 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/04 22:24:24 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cra;

	if (lst != NULL && del)
	{
		tmp = NULL;
		while (lst)
		{
			cra = ft_lstnew((*f)(lst->key), 0,  0, 0);
			if (!cra)
			{
				ft_lstclear(&cra, del);
				return (NULL);
			}
			ft_lstadd_back(&tmp, cra);
			lst = lst->next;
		}
		return (tmp);
	}
	return (NULL);
}
