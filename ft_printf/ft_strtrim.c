/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:25:09 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 14:08:56 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int			str_size;
	char		*new_s;

	if (!s1 || !set)
	{
		return (0);
	}
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	str_size = ft_strlen(s1);
	while (str_size && ft_strchr(set, s1[str_size]))
		str_size--;
	new_s = ft_substr(s1, 0, str_size + 1);
	return (new_s);
}
