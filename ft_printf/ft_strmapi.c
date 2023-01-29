/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:50:55 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 13:50:05 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char				*copy;
	unsigned int		x;

	x = -1;
	if (!s || !f)
		return (NULL);
	copy = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	while (s[++x])
		copy[x] = (f)(x, s[x]);
	copy[x] = '\0';
	return (copy);
}
