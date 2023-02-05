/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:07:04 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/05 15:59:43 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_red_after(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] != ' ')
			|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] != ' '))
		{
			count++;
			i += 2;
		}
		else if ((str[i] == '<' && str[i + 1] != ' ' && str[i + 1] != '<')
			|| (str[i] == '>' && str[i + 1] != ' ' && str[i + 1] != '>'))
			count++;
		i++;
	}
	return (count);
}

char	ft_quote_zero_one(char str, char ch, int *check_quote)
{
	if (!(*check_quote) || ch == str)
	{
		if (str == '\"' || str == '\'')
		{
			*check_quote = !(*check_quote);
			ch = str;
		}
	}
	return (ch);
}

void	ft_copy_dred_new_string(char *str, char *new_str, int *i, int *j)
{
	new_str[(*j)++] = str[(*i)++];
	new_str[(*j)++] = str[(*i)++];
	new_str[(*j)++] = ' ';
}

void	ft_copy_sred_new_string(char *str, char *new_str, int *i, int *j)
{
	if (str[(*i) + 1] != '<' && \
		str[(*i) + 1] != '>' && str[(*i) + 1] != ' ')
	{
		new_str[(*j)++] = str[(*i)++];
		new_str[(*j)++] = ' ';
	}
	else
		new_str[(*j)++] = str[(*i)++];
}
