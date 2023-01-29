/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:01:05 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 14:06:29 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		x;

	x = ft_strlen(s);
	while (x >= 0)
	{
		if (s[x] == (char)c)
			return ((char *)&s[x]);
		x--;
	}
	return (0);
}
