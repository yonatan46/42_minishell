/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker_qoutes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:07:23 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/27 16:01:02 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_qoutes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			if (ft_check_quote(str, '\'', &i))
				return (1);
		}
		else if (str[i] == '\"')
		{
			if (ft_check_quote(str, '\"', &i))
				return (1);
		}
	}
	return (0);
}

/* check if the string has || or |; or ;; that it's error*/
int	ft_check_sem_pipe(char *str, int i)
{
	int	count;

	count = ft_strlen(str);
	if (str[i] == '|' && str[i + 1] == '|')
		return (1);
	else if (str[i] == '|' && str[i + 1] == ';')
		return (1);
	else if (str[i] == ';' && str[i + 1] == ';')
		return (1);
	else if (str[count - 1] == '|' || str[count - 1] == '<' || str[count - 1] == '>')
		return (1);
	return (0);
}

int	ft_check_quote(char *str, char qute, int *i)
{
	int		d_quotes;
	int		count_quotes;
	char	q1;

	d_quotes = 0;
	count_quotes = 0;
	if (qute == '\'')
		q1 = '\"';
	else if (qute == '\"')
		q1 = '\'';
	while (str[*i])
	{
		if (str[*i] == qute)
			d_quotes = !d_quotes;
		if (!d_quotes)
			return (0);
		if (str[*i] == q1 && !d_quotes)
			count_quotes++;
		(*i)++;
	}
	if (d_quotes)
		return (1);
	return (0);
}