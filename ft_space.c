/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:04:57 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/02 13:24:35 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_clean_spaces(char *str)
{
	int i;
	int j;
	int k;
	int check_quote;
	char ch;
	
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
		// if (str[i] == '\'' || str[i] == '\"')
		// 	check_quote = !check_quote;
		if (check_quote)
			str[k++] = str[i];
		else if (str[i] != ' ')
			str[k++] = str[i];
		else if (str[i] == ' '  && str[i + 1] != ' ')
					str[k++] = str[i];
		i++;
	}
	str[k] = '\0';
	return (str);
}

int ft_trim_space(char *str, char c)
{
	int i;
	int j;
	
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

char **ft_clean_sp_struct(char **str)
{
	int i = 0;
	while (str[i])
	{
		str[i] = ft_clean_spaces(str[i]);
		i++;
	}
	return (str);
}