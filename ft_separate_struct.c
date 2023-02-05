/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:07:29 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/05 15:16:00 by dkaratae         ###   ########.fr       */
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
	if (f_struct[i].f_cmd[j])
		f_struct[i].red[r]->red_name = ft_strdup(f_struct[i].f_cmd[j]);
}

void	ft_copy_to_arg(t_pipe *f_struct, int i, int j, int *g)
{
	f_struct[i].arg[*g] = ft_strdup(f_struct[i].f_cmd[j]);
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
			if (f_struct[v[0]].f_cmd[v[1]][0] == '<' || \
			f_struct[v[0]].f_cmd[v[1]][0] == '>')
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
