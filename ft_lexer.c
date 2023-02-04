/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:53:15 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/04 15:29:14 by dkaratae         ###   ########.fr       */
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

int ft_count_quotes(char *str, char c)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}

char *ft_del_quotes(char *str, int *i, char c)
{
	int j;
	int count;
	int count_quotes;
	char *ch;

	// i = 0;
	j = 0;
	count_quotes = 0;
	count = ft_strlen(str);
	if (c == '\'')
		count_quotes = ft_count_quotes(str, '\'');
	else if (c == '\"')
		count_quotes = ft_count_quotes(str, '\"');
	count = count - count_quotes;
	ch = (char*)malloc(sizeof(char) * (count + 1));
	while (str[(*i)])
	{
		if (str[(*i)] != c)
		{
			ch[j] = str[(*i)];
			j++;
		}
		(*i)++;
	}
	ch[j] = '\0';
 	return (ch);
}

void ft_delete_cmd_quotes(t_pipe *f_struct)
{
	int i;
	int j;
	
	i = -1;
	while (f_struct[++i].cmd)
	{
		j = -1;
		while (f_struct[i].cmd[++j])
		{
			if (f_struct[i].cmd[j] == '\'')
			{
				// ch = ft_del_quotes(f_struct[i].arg[j], '\'');
				f_struct[i].cmd = ft_del_quotes(f_struct[i].cmd, &j, '\'');
				// printf("line - %s \n", f_struct[i].cmd[j]);
			}
			else if (f_struct[i].cmd[j] == '\"')
			{
				// ch = ft_del_quotes(f_struct[i].cmd[j], '\'');
				f_struct[i].cmd = ft_del_quotes(f_struct[i].cmd, &j, '\"');
				// printf("line - %s \n", f_struct[i].arg[j]);
			}
		}
	}
}
// void ft_delete_redname_quotes(t_pipe *f_struct)
// {
// 	int i;
// 	int j;
	
// 	i = -1;
// 	while (f_struct[++i].red)
// 	{
// 		j = -1;
// 		while (f_struct[i].red[++j])
// 		{
// 			if (f_struct[i].cmd[j] == '\'')
// 			{
// 				// ch = ft_del_quotes(f_struct[i].arg[j], '\'');
// 				f_struct[i].cmd = ft_del_quotes(f_struct[i].red, &j, '\'');
// 				// printf("line - %s \n", f_struct[i].cmd[j]);
// 			}
// 			else if (f_struct[i].cmd[j] == '\"')
// 			{
// 				// ch = ft_del_quotes(f_struct[i].cmd[j], '\'');
// 				f_struct[i].cmd = ft_del_quotes(f_struct[i].cmd, &j, '\"');
// 				// printf("line - %s \n", f_struct[i].arg[j]);
// 			}
// 		}
// 	}
// }

void ft_delete_arg_quotes(t_pipe *f_struct)
{
	int i;
	int j;
	int z;
	int k;
	int f;
	char *ch;
	char *ch1;
	
	i = -1;
	k = 0;
	while (f_struct[++i].arg)
	{
		j = -1;
		while (f_struct[i].arg[++j])
		{
			z = -1;
			while (f_struct[i].arg[j][++z])
			{
				if (f_struct[i].arg[j][z] == '\'')
				{
										f = z;
					ch = ft_del_quotes(f_struct[i].arg[j], &z, '\'');
					ch1 = ft_substr(f_struct[i].arg[j], k, f);
					// printf("F-> %s\n", ch1);
					f_struct[i].arg[j] = ft_strjoin(ch1, ch);
					// f_struct[i].arg[j] = ft_del_quotes(f_struct[i].arg[j], &z, '\'');
					// printf("line - %s \n", f_struct[i].arg[j]);
				}
				else if (f_struct[i].arg[j][z] == '\"')
				{
					f = z;
					ch = ft_del_quotes(f_struct[i].arg[j], &z, '\"');
					ch1 = ft_substr(f_struct[i].arg[j], k, f);
					// printf("F-> %s\n", ch1);
					f_struct[i].arg[j] = ft_strjoin(ch1, ch);
					// f_struct[i].arg[j] = ft_del_quotes(f_struct[i].arg[j], &z, '\"');
					// printf("line - %s \n", f_struct[i].arg[j]);
				}
			}
		}
	}
}

void ft_delete_redname_quotes(t_pipe *f_struct)
{
	int i;
	int j;
	int z;
	int k;
	int f;
	char *ch;
	char *ch1;
	
	i = -1;
	k = 0;
	while (f_struct[++i].red)
	{
		j = -1;
		while (f_struct[i].red[++j])
		{
			z = -1;
			while (f_struct[i].red[j]->red_name[++z])
			{
				// printf("REDNAME: %c\n", f_struct[i].red[j]->red_name[z]);
				if (f_struct[i].red[j]->red_name[z] == '\'')
				{
					f = z;
					ch = ft_del_quotes(f_struct[i].red[j]->red_name, &z, '\'');
					ch1 = ft_substr(f_struct[i].red[j]->red_name, k, f);
					// printf("F-> %s\n", ch1);
					f_struct[i].red[j]->red_name = ft_strjoin(ch1, ch);
					// f_struct[i].arg[j] = ft_del_quotes(f_struct[i].arg[j], &z, '\'');
					// printf("line - %s \n", f_struct[i].arg[j]);
				}
				else if (f_struct[i].red[j]->red_name[z] == '\"')
				{
					f = z;
					ch = ft_del_quotes(f_struct[i].red[j]->red_name, &z, '\"');
					ch1 = ft_substr(f_struct[i].red[j]->red_name, k, f);
					// printf("F-> %s\n", ch1);
					f_struct[i].red[j]->red_name = ft_strjoin(ch1, ch);
					// f_struct[i].arg[j] = ft_del_quotes(f_struct[i].arg[j], &z, '\"');
					// printf("line - %s \n", f_struct[i].arg[j]);
				}
			}
		}
	}
}

void ft_delete_all_qoutes(t_pipe *f_struct)
{
	ft_delete_cmd_quotes(f_struct);
	ft_delete_arg_quotes(f_struct);
	ft_delete_redname_quotes(f_struct);
}

t_pipe *ft_lexer(char *str, char **env)
{
	(void)env;
	int i;
	char **vars;
	int pipes_num;
	t_pipe *f_struct;

	i = 0;
	pipes_num = ft_calc(str, '|');
	str = ft_add_sp_redname(str);
	vars = ft_clean_sp_struct(ft_separate_sp_pipe(str, '|'));
	f_struct = ft_calloc(sizeof(t_pipe), pipes_num + 2);
	while (vars[i])
	{
		// printf("----<Structure = %i>----\n", i);
		f_struct[i].f_cmd =  ft_separate_sp_pipe(vars[i], ' ');
		f_struct[i].cmd_len = pipes_num + 1;
		// print_2d(f_struct[i].f_cmd);
		// printf("-----------------------\n");
		i++;
	}
	ft_count_struct(f_struct);
	ft_delete_all_qoutes(f_struct);
	return(f_struct);
	// ft_print3(f_struct);
	// ft_print3(f_struct);
}

