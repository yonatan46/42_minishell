/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:56:25 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 13:31:19 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	char	*str;
	int		x;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	x = -1;
	y = 0;
	str = malloc(sizeof(char) * (size1 + size2) + 1);
	if (!str)
		return (NULL);
	while (s1[++x] != '\0')
		str[x] = s1[x];
	while (s2[y] != '\0')
		str[x++] = s2[y++];
	str[x] = '\0';
	return (str);
}
