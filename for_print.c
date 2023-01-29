/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:04:32 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/27 13:00:48 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_2d(char **str)
{
	int i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void ft_print_cmd(t_pipe *f_struct)
{
	int i;
	int j;

	i = 0;
	while (f_struct[i].arg || f_struct[i].red)
	{
	printf("---------<Structure = %i>--------\n", i);
	printf("---------<cmd_len     = %d>--------\n", f_struct[i].cmd_len);
	printf("---------<red_len     = %d>--------\n", f_struct[i].red_len);
		printf("CMD = %s\n", f_struct[i].cmd);	
		j =	0;
		while (f_struct[i].arg && f_struct[i].arg[j])
		{
			printf("	ARG = %s\n", f_struct[i].arg[j]);
			j++;
		}
		j =	0;
		while (f_struct[i].red && f_struct[i].red[j])
		{
			printf("		SIGN = %s\n", f_struct[i].red[j]->red_sign);
			printf("		NAME = %s\n", f_struct[i].red[j]->red_name);
			j++;
		}
		i++;
	}
	printf("----------------------------------\n");
 }


// void ft_print3(t_pipe *f_struct)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (f_struct[i].red)
// 	{
// 		j =	0;
// 		while (f_struct[i].red[j])
// 		{
// 			printf("SIGN %s\n", f_struct[i].red[j]->red_sign);
// 			printf("NAME %s\n", f_struct[i].red[j]->red_name);
// 			j++;
// 		}
// 		i++;	
// 	}
//  }

// void ft_print5(t_pipe *f_struct)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (f_struct[i].arg)
// 	{
// 		j =	0;
// 		while (f_struct[i].arg[j])
// 		{
// 			printf("ARG i=%d  j=%d %s\n", i, j, f_struct[i].arg[j]);
// 			j++;
// 		}
// 		i++;	
// 	}
//  }


// void ft_print4(t_pipe *f_struct)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (f_struct[i].f_cmd)
// 	{
// 		j =	0;
// 		while (f_struct[i].f_cmd[j])
// 		{
// 			printf("SIGN %s\n", f_struct[i].f_cmd[j]);
// 			j++;
// 		}
// 		i++;	
// 	}
//  }

// void ft_print_cmd(t_pipe *f_struct)
// {
// 	int i;

// 	i = 0;
// 	while (f_struct[i].cmd)
// 	{
// 		printf("CMD = %s\n", f_struct[i].cmd);
// 		i++;	
// 	}
//  }
// void ft_print_str(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("SIGN = %s\n", str[i]);
// 		i++;	
// 	}
//  }

 void	ft_print_arg(char **vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars[i])
	{
		j = 0;
		while (vars[i][j])
		{
			printf("%c", vars[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}