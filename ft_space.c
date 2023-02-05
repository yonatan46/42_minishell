/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:04:57 by dkaratae          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/04 22:45:54 by dkaratae         ###   ########.fr       */
=======
/*   Updated: 2023/02/04 23:00:24 by yonamog2         ###   ########.fr       */
>>>>>>> 13e1b799c82fd8601878275121dd598ee2bc5a74
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy_after_clean_sp(char *str, int *i, int *k, int check_quote)
{
	if (check_quote)
		str[(*k)++] = str[*i];
	else if (str[*i] != ' ')
		str[(*k)++] = str[*i];
	else if (str[*i] == ' ' && str[*i + 1] != ' ')
		str[(*k)++] = str[*i];
	return (str);
}

char	*ft_clean_spaces(char *str)
{
	int		i;
	int		j;
	int		k;
	int		check_quote;
	char	ch;

	k = 0;
	check_quote = 0;
	i = ft_trim_space(str, 'b');
	j = ft_trim_space(str, 'e');
	while (i <= j)
	{
		if (!check_quote || ch == str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				ch = str[i];
				check_quote = !check_quote;
			}
		}
		str = ft_copy_after_clean_sp(str, &i, &k, check_quote);
		i++;
	}
	str[k] = '\0';
	return (str);
}

int	ft_trim_space(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = (ft_strlen(str) - 1);
	if (c == 'b')
	{
		while (ft_isspace(str[i]))
			i++;
		return (i);
	}
	else if (c == 'e')
	{
		while (j >= 0 && ft_isspace(str[j]))
			j--;
		return (j);
	}
	return (0);
}

char	**ft_clean_sp_struct(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_clean_spaces(str[i]);
		i++;
	}
	return (str);
}
