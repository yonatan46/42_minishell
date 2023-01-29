/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:33:34 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 14:28:42 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str1, const void *str2, size_t n)
{
	unsigned int		i;
	unsigned char		*dest;
	unsigned const char	*str;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	i = -1;
	dest = (unsigned char *)str1;
	str = (unsigned char *)str2;
	while (++i < n)
		*((char *)dest + i) = *((char *)str + i);
	return (dest);
}
