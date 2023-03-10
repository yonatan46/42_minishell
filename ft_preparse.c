/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:42:54 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/20 14:38:01 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_check_count_red(char *str, int i, char c)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == c || ft_isspace(str[i]))
		{
			if (str[i] == c)
				count++;
		}
		else
			break ;
		i++;
	}
	if (count > 2)
		return (1);
	return (0);
}

int	ft_check_red_pipe(char *str)
{
	int	i;

	i = -1;
	if (ft_check_red_pipe_dub(str))
		return (1);
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

int	ft_check_count_red_one(char *str)
{
	int		i;
	char	ch;
	int		check_quote;

	i = -1;
	check_quote = 0;
	while (str[++i])
	{
		ch = ft_quote_zero_one(str[i], ch, &check_quote);
		if (str[i] == '>' && !check_quote)
		{
			if (ft_check_count_red(str, i, '>'))
				return (1);
		}
		else if (str[i] == '<' && !check_quote)
		{
			if (ft_check_count_red(str, i, '<'))
				return (1);
		}
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
	if (ft_check_count_red_one(str))
		return (1);
	i = -1;
	while (str[++i])
	{
		ch = ft_quote_zero_one(str[i], ch, &check_quote);
		if (ft_check_sem_pipe(str, i) && !check_quote)
			return (1);
	}
	if (ft_check_red_pipe(str))
		return (1);
	return (0);
}
