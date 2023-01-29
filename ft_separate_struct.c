/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:07:29 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/27 14:56:17 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  ft_copy_red_sign(t_pipe *f_struct, int i, int j, int r)
{
	f_struct[i].red[r] = ft_calloc(sizeof(t_red), 1);
	f_struct[i].red[r]->red_sign = ft_strdup(f_struct[i].f_cmd[j]);
}

void ft_copy_red_name(t_pipe *f_struct, int i, int j, int r)
{
	if (f_struct[i].f_cmd[j])
		f_struct[i].red[r]->red_name = ft_strdup(f_struct[i].f_cmd[j]);	
	// printf("redL: %s\n", f_struct[i].f_cmd[j]);
}

void ft_count_struct(t_pipe *f_struct)
{
	int i;
	int j;
	int r;
	// int k;
	int g;
	int count_all;
	int count_red;
	int flag;

	i = 0;
	// k = 0;
		count_all = 0;
	count_red = 0;
	while (f_struct[i].f_cmd)
	{
		j = 0;
		r = 0;
		count_all = ft_count_arg(f_struct[i].f_cmd);
		// printf("count_all : %d\n", count_all);
		count_red = ft_count_red(f_struct[i].f_cmd);
		// printf("count_red : %d\n", count_red);
		count_all = (count_all - (count_red + count_red));
		// printf("count_all_after : %d\n", count_all);
		if (count_red == 0)
			f_struct[i].red = NULL;
		else
		{
			f_struct[i].red = ft_calloc(sizeof(t_pipe), count_red);
			f_struct[i].red_len = count_red;
		}

		if (count_all == 0)
			f_struct[i].arg = NULL;
		else
			f_struct[i].arg = ft_calloc(sizeof(t_pipe), count_all + 1);
		// f_struct[i].red = ft_calloc(sizeof(t_pipe), count_red);
		// f_struct[i].arg = ft_calloc(sizeof(t_pipe), count_all);
		

		g = 0;
		flag = 0;
		while (f_struct[i].f_cmd[j])
		{
			if (f_struct[i].f_cmd[j][0] == '<' || f_struct[i].f_cmd[j][0] == '>')
			{
				ft_copy_red_sign(f_struct, i , j++, r);
				ft_copy_red_name(f_struct, i , j, r++);
				// break;
			}
			else if (count_all >= 1 && flag == 0)
			{
				f_struct[i].cmd = ft_strdup(f_struct[i].f_cmd[j]);
				flag = 1;
			}
			else
			{
				if (g == 0)
				{
					f_struct[i].arg[g] = ft_strdup(f_struct[i].cmd);
					g++;
				}
				f_struct[i].arg[g] = ft_strdup(f_struct[i].f_cmd[j]);
				g++;
			}
			j++;
		}
		i++;
	}
}