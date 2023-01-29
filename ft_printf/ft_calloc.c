/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:23:13 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 09:50:51 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*create;

	create = malloc(size * count);
	if (!create || size >= SIZE_MAX)
		return (NULL);
	ft_bzero(create, count * size);
	return ((void *)(create));
}
