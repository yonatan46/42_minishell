/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:20:44 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 13:25:26 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_occ(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static	int	do_pls(const char *s_1, char c_1, char **str_1, int set1)
{
	int	y1;
	int	x1;

	x1 = 0;
	y1 = 0;
	while (s_1[x1] != '\0')
	{
		if (s_1[x1] == c_1 && ft_isprint(s_1[x1]))
		{
			while (s_1[x1] == c_1)
				x1++;
			set1 = x1;
		}
		else if (s_1[x1] != c_1 && ft_isprint(s_1[x1]))
		{
			while (s_1[x1] != c_1 && s_1[x1] != '\0')
				x1++;
			str_1[y1] = ft_substr (s_1, set1, x1 - set1);
			set1 = x1 + 1;
			if (s_1[x1] != '\0')
				x1++;
			y1++;
		}
	}
	return (y1);
}

char	**ft_split(const char *s, char c)
{
	char	**str;
	int		y;
	int		set;

	if (!s)
		return (NULL);
	y = 0;
	set = 0;
	str = (char **)malloc (sizeof (char *) * ((count_occ(s, c) + 1)));
	if (!str)
		return (NULL);
	y = do_pls(s, c, str, set);
	str[y] = NULL;
	return (str);
}
