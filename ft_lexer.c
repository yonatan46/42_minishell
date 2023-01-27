/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:53:15 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/27 15:13:11 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_arg(char **str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count++;
		i++;
	}
	return (count);
}

void ft_lexer(char *str)
{
	int i;
	char **vars;
	int pipes_num;
	t_data *f_struct;

	i = 0;
	pipes_num = ft_calc(str, '|');
	str = ft_add_sp_redname(str);
	vars = ft_clean_sp_struct(ft_separate_sp_pipe(str, '|'));
	f_struct = ft_calloc(sizeof(t_data), pipes_num + 2);
	while (vars[i])
	{
		// printf("----<Structure = %i>----\n", i);
		f_struct[i].f_cmd =  ft_separate_sp_pipe(vars[i], ' ');
		// print_2d(f_struct[i].f_cmd);
		// printf("-----------------------\n");
		i++;
	}
	ft_count_struct(f_struct);
	ft_print_cmd(f_struct);
	// ft_print3(f_struct);
	// ft_print3(f_struct);
}

