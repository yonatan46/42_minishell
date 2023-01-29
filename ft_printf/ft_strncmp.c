/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:15:05 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 14:25:01 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	if (n == 0)
		return (0);
	while ((s1[x] != '\0') && (s2[x] != '\0') && (x < n))
	{
		if (s1[x] != s2[x])
		{
			return (((unsigned char *)s1)[x] - ((unsigned char *)s2)[x]);
		}
		x++;
	}
	if (x != n)
		return (((unsigned char *)s1)[x] - ((unsigned char *)s2)[x]);
	return (0);
}
