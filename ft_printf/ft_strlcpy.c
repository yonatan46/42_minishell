/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:26:55 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 13:44:44 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	x;

	x = 0;
	if (size > 0)
	{
		while (x < size - 1 && src[x] != '\0')
		{
			dst[x] = src[x];
			x++;
		}		
		dst[x] = '\0';
	}
	while (src[x] != '\0')
		x++;
	return (x);
}
