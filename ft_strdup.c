/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:16:11 by yonamog2          #+#    #+#             */
/*   Updated: 2022/12/23 14:08:33 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
