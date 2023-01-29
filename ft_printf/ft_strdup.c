/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:16:11 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 13:28:28 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	int		x;
	int		size;
	char	*dup;

	size = ft_strlen(s1) + 1;
	x = -1;
	dup = malloc(sizeof(char) * size);
	if (!dup)
		return (NULL);
	while (s1[++x] != '\0')
		dup[x] = s1[x];
	dup[x] = '\0';
	return (dup);
}
