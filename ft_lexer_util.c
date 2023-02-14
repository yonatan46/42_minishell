/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:01:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 19:26:22 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_structs_util(t_pipe *f_struct, t_data *proc)
{
	if (f_struct[proc->i].arg[1])
	{
		f_struct[proc->i].cmd = expand(f_struct[proc->i].arg[1], proc);
		f_struct[proc->i].arg[1] = NULL;
	}
	else
		f_struct[proc->i].cmd = NULL;
}

void	expand_structs_util2(t_pipe *f_struct, t_data *proc)
{
	while (f_struct[proc->i].arg && f_struct[proc->i].arg[proc->x])
	{
		f_struct[proc->i].arg[proc->x] = expand \
		(f_struct[proc->i].arg[proc->x], proc);
		proc->x++;
	}
}

void	expand_structs(t_pipe *f_struct, t_data *proc)
{
	char	*tmp;

	proc->i = -1;
	proc->x = 0;
	while (++proc->i < f_struct->cmd_len)
	{
		tmp = expand(f_struct[proc->i].cmd, proc);
		if (tmp == NULL)
			expand_structs_util(f_struct, proc);
		else
			f_struct[proc->i].cmd = tmp;
		expand_structs_util2(f_struct, proc);
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
	if (str == NULL)
		return (0);
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}
