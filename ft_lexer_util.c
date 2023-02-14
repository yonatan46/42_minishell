/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:01:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 13:04:41 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_structs(t_pipe *f_struct, t_data *proc)
{
	int	x;
	int	i;

	i = 0;
	x = 0;
	while (i < f_struct->cmd_len)
	{
		f_struct[i].cmd = expand(f_struct[i].cmd, proc);
		x = 0;
		while (f_struct[i].arg && f_struct[i].arg[x])
		{
			f_struct[i].arg[x] = expand(f_struct[i].arg[x], proc);
			x++;
		}
		x = 0;
		while (x < f_struct[i].red_len)
		{
			f_struct[i].red[x]->red_sign = \
			expand(f_struct[i].red[x]->red_sign, proc);
			f_struct[i].red[x]->red_name = \
			expand(f_struct[i].red[x]->red_name, proc);
			x++;
		}
		i++;
	}
}

int	ft_count_arg(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	ft_count_quotes(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}
