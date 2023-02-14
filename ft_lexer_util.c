/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:01:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 18:11:33 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_structs(t_pipe *f_struct, t_data *proc)
{
	proc->i = -1;
	proc->x = 0;
	while (++proc->i < f_struct->cmd_len)
	{
		f_struct[proc->i].cmd = expand(f_struct[proc->i].cmd, proc);
		proc->x = 0;
		while (f_struct[proc->i].arg && f_struct[proc->i].arg[proc->x])
		{
			f_struct[proc->i].arg[proc->x] = (expand \
			(f_struct[proc->i].arg[proc->x], proc));
			proc->x++;
		}
		proc->x = 0;
		while (proc->x < f_struct[proc->i].red_len)
		{
			f_struct[proc->i].red[proc->x]->red_sign = \
			expand(f_struct[proc->i].red[proc->x]->red_sign, proc);
			f_struct[proc->i].red[proc->x]->red_name = \
			expand(f_struct[proc->i].red[proc->x]->red_name, proc);
			proc->x++;
		}
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
