/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:07:25 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/05 15:09:09 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_equal_dred(char *str, int i, int check_quote)
{
	if ((!check_quote && (str[i] == '<' && \
		str[i + 1] == '<' && str[i + 2] != ' ')) \
			|| (!check_quote && (str[i] == '>' && \
			str[i + 1] == '>' && str[i + 2] != ' ')))
		return (1);
	return (0);
}

char	*ft_add_sp_red_after(char *str)
{
	int		v[4];
	int		check_quote;
	char	*new_str;
	char	ch;

	v[0] = 0;
	v[1] = 0;
	check_quote = 0;
	v[2] = ft_strlen(str);
	v[3] = ft_count_red_after(str);
	new_str = (char *)malloc(sizeof(char) * (v[2] + v[3] + 1));
	while (v[0] < v[2])
	{
		ch = ft_quote_zero_one(str[v[0]], ch, &check_quote);
		if (ft_check_equal_dred(str, v[0], check_quote))
			ft_copy_dred_new_string(str, new_str, &v[0], &v[1]);
		else if (!check_quote && (str[v[0]] == '<' || str[v[0]] == '>'))
			ft_copy_sred_new_string(str, new_str, &v[0], &v[1]);
		else
			new_str[v[1]++] = str[v[0]++];
	}
	new_str[v[1]] = '\0';
	return (new_str);
}

int	ft_count_red_before(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((i != 0 && str[i] == '<' && str[i - 1] != ' ') \
			|| (i != 0 && str[i] == '>' && str[i - 1] != ' '))
		{
			if ((str[i - 1] != '<' && str[i - 1] != '>'))
				count++;
			else
				i++;
		}
		i++;
	}
	return (count);
}

void	ft_copy_sred_before(char *str, char *new_str, int *i, int *j)
{
	if ((str[(*i) - 1] != '<' && str[(*i) - 1] != '>'))
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = str[(*i)++];
	}
	else
		new_str[(*j)++] = str[(*i)++];
}

char	*ft_add_sp_red_before(char *str)
{
	int		v[4];
	int		q;
	char	*new_str;
	char	ch;

	v[0] = 0;
	v[1] = 0;
	q = 0;
	v[2] = ft_strlen(str);
	v[3] = ft_count_red_before(str);
	new_str = (char *)malloc(sizeof(char) * (v[2] + v[3] + 1));
	while (v[0] < v[2])
	{
		ch = ft_quote_zero_one(str[v[0]], ch, &q);
		if ((!q && (v[0] != 0 && str[v[0]] == '<' && str[v[0] - 1] != ' ')) \
			|| (!q && (v[0] != 0 && str[v[0]] == '>' && str[v[0] - 1] != ' ')))
			ft_copy_sred_before(str, new_str, &v[0], &v[1]);
		else
			new_str[v[1]++] = str[v[0]++];
	}
	new_str[v[1]] = '\0';
	return (new_str);
}
