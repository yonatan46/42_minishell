/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 15:14:29 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/20 14:36:08 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_red_pipe(char **str, int count_all, int count_red)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] == '>') && (str[i][j + 1] == '\0'))
			{
				count_all = count_all - count_red;
				return (count_all);
			}
			j++;
		}
		i++;
	}
	count_all = count_all - (count_red + count_red);
	return (count_all);
}

int	ft_allocate_memory_red_arg(t_pipe *f_struct, int *i)
{
	int		count_all;
	int		count_red;

	count_all = 0;
	count_red = 0;
	count_all = ft_count_arg(f_struct[*i].f_cmd);
	count_red = ft_count_red(f_struct[*i].f_cmd);
	f_struct[*i].red_len = count_red;
	count_all = ft_count_red_pipe(f_struct[*i].f_cmd, count_all, count_red);
	if (count_red == 0)
		f_struct[*i].red = NULL;
	else
		f_struct[*i].red = ft_calloc(sizeof(t_data), count_red);
	if (count_all == 0)
		f_struct[*i].arg = NULL;
	else
		f_struct[*i].arg = ft_calloc(sizeof(t_data), count_all + 1);
	return (count_all);
}

int	ft_check_red_sp_nothing(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '|')
			return (1);
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] == ' ')
		{
			i++;
			while (ft_isspace(str[i]))
				i++;
			if (str[i] == '\0')
				return (1);
			else if (str[i] == '<' || str[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_check_loop_space_dub(char *str, int *i)
{
	++(*i);
	while (ft_isspace(str[++(*i)]))
		(*i)++;
}

int	ft_check_red_pipe_dub(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' && str[i + 1] == ' ')
		{
			ft_check_loop_space_dub(str, &i);
				if (str[i] == '|')
					return (1);
		}
		else if (str[i] == '<' && str[i + 1] == ' ')
		{
			ft_check_loop_space_dub(str, &i);
			if (str[i] == '|')
				return (1);
		}
	}
	return (0);
}
