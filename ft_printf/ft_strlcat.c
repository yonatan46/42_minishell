/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 10:11:24 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 13:42:43 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, unsigned int size)
{
	unsigned int		i;
	unsigned int		j;

	i = 0;
	while (i < size && *dst)
	{
		dst++;
		i++;
	}
	if (i == size)
		return (i + ft_strlen(src));
	j = -1;
	while (src[++j])
		if (j < (size - i) - 1)
			*dst++ = src[j];
	*dst = '\0';
	return (j + i);
}
