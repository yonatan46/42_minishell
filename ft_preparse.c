/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:42:54 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/08 18:57:15 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t' || \
		ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

int	ft_check_loop_space(char *str, int *i)
{
	int	count;

	count = 0;
	while (ft_isspace(str[++(*i)]))
		count++;
	if (count == 0)
		return (1);
	return (0);
}

int	ft_check_red_pipe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>')
		{
			if (!ft_check_loop_space(str, &i))
				if (str[i] == '|')
					return (1);
		}
		else if (str[i] == '<')
		{
			ft_check_loop_space(str, &i);
			if (str[i] == '|')
				return (1);
		}
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_preparsing(char *str)
{
	int		i;
	int		check_quote;
	char	ch;

	check_quote = 0;
	i = 0;
	while ((ft_isspace(str[i])))
		i++;
	if (str[i] == '|' || str[i] == ';')
		return (1);
	if (ft_check_qoutes(str))
		return (1);
	if (ft_check_red_pipe(str))
		return (1);
	i = -1;
	while (str[++i])
	{
		ch = ft_quote_zero_one(str[i], ch, &check_quote);
		if (ft_check_sem_pipe(str, i) && !check_quote)
			return (1);
	}
	return (0);
}
