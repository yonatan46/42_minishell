/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:07:29 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/20 16:21:59 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_red_sign(t_pipe *f_struct, int i, int j, int r)
{
	f_struct[i].red[r] = ft_calloc(sizeof(t_red), 1);
	f_struct[i].red[r]->red_sign = ft_strdup(f_struct[i].f_cmd[j]);
}

void	ft_copy_red_name(t_pipe *f_struct, int i, int j, int r)
{
	int	g;

	g = -1;
	f_struct[i].red[r]->flag = 0;
	if (f_struct[i].f_cmd[j])
	{
		f_struct[i].red[r]->red_name = ft_strdup(f_struct[i].f_cmd[j]);
	}
	while (f_struct[i].red[r]->red_name[++g])
	{
		if (f_struct[i].red[r]->red_name[g] == '\'' || \
		f_struct[i].red[r]->red_name[g] == '\"')
		{
			f_struct[i].red[r]->flag = 1;
			break ;
		}
	}
}

void	ft_copy_to_arg(t_pipe *f_struct, int i, int j, int *g)
{
	f_struct[i].arg[*g] = ft_strdup(f_struct[i].f_cmd[j]);
	f_struct[i].arg_len++;
	(*g)++;
}

void	ft_copy_to_red_sign_name(t_pipe *f_struct, int i, int *j, int *r)
{
	ft_copy_red_sign(f_struct, i, (*j)++, (*r));
	ft_copy_red_name(f_struct, i, (*j), (*r)++);
}

void	ft_count_struct(t_pipe *f_struct)
{
	int		v[6];

	v[0] = -1;
	while (f_struct[++v[0]].f_cmd)
	{
		v[1] = -1;
		v[2] = 0;
		v[3] = 0;
		v[4] = 0;
		v[5] = ft_allocate_memory_red_arg(f_struct, &v[0]);
		while (f_struct[v[0]].f_cmd[++v[1]])
		{
			if (check_red_name(f_struct[v[0]].f_cmd[v[1]]) == 1)
				ft_copy_to_red_sign_name(f_struct, v[0], &v[1], &v[2]);
			else if (v[5] >= 1 && v[4] == 0)
			{
				f_struct[v[0]].cmd = ft_strdup(f_struct[v[0]].f_cmd[v[1]]);
				ft_copy_to_arg(f_struct, v[0], v[1], &v[3]);
				v[4] = 1;
			}
			else
				ft_copy_to_arg(f_struct, v[0], v[1], &v[3]);
		}
	}
}
