/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:56:25 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/06 13:47:42 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*ret;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1)
		return (NULL);
	if (!s2)
		return (s1);
	ret = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!ret)
		return (NULL);
	x = 0;
	y = -1;
	if (s1)
		while (s1[++y] != '\0')
			ret[y] = s1[y];
	while (s2[x] != '\0')
		ret[y++] = s2[x++];
	ret[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (ret);
}

char	*ftt_strjoin(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*ret;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	ret = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!ret)
		return (NULL);
	x = 0;
	y = -1;
	if (s1)
		while (s1[++y] != '\0')
			ret[y] = s1[y];
	while (s2[x] != '\0')
		ret[y++] = s2[x++];
	ret[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (ret);
}
