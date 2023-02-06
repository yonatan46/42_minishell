/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:53:15 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/06 16:53:49 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_delete_argquotes(t_pipe *f_struct, char *str, int *i, int *j)
{
	int		z;
	int		f;
	int		k;
	char	*ch;
	char	*ch1;

	z = -1;
	k = 0;
	while (str[++z])
	{
		if (str[z] == '\'')
		{
			f = z;
			ch = ft_del_quotes(str, &z, '\'');
			ch1 = ft_substr(str, k, f);
			f_struct[*i].arg[*j] = ft_strjoin(ch1, ch);
		}
		else if (str[z] == '\"')
		{
			f = z;
			ch = ft_del_quotes(str, &z, '\"');
			ch1 = ft_substr(str, k, f);
			f_struct[*i].arg[*j] = ft_strjoin(ch1, ch);
		}
	}
}

void	ft_delete_arg_quotes(t_pipe *f_struct)
{
	int		i;
	int		j;

	i = -1;
	while (f_struct[++i].arg)
	{
		j = -1;
		while (f_struct[i].arg[++j])
			ft_delete_argquotes(f_struct, f_struct[i].arg[j], &i, &j);
	}
}

t_pipe	*ft_lexer(char *str, t_data	*proc)
{
	(void)proc;
	int		i;
	int		x;
	char	**vars;
	int		pipes_num;
	t_pipe	*f_struct;

	i = 0;
	pipes_num = ft_calc(str, '|');
	str = ft_add_sp_redname(str);
	vars = ft_clean_sp_struct(ft_separate_sp_pipe(str, '|'));
	f_struct = ft_calloc(sizeof(t_pipe), pipes_num + 2);
	while (vars[i])
	{
		f_struct[i].f_cmd = ft_separate_sp_pipe(vars[i], ' ');
		f_struct[i].cmd_len = pipes_num + 1;
		i++;
	}
	ft_count_struct(f_struct);
	i = 0;
	x = 0;
	while (i < f_struct->cmd_len)
	{
		f_struct[i].cmd = expand(f_struct[i].cmd, proc);
		x = 0;
		while (f_struct[i].arg[x])
		{
			f_struct[i].arg[x] = expand(f_struct[i].arg[x], proc);
			x++;
		}
		x = 0;
		while (x < f_struct[i].red_len)
		{
			f_struct[i].red[x]->red_sign = expand(f_struct[i].red[x]->red_sign, proc);
			f_struct[i].red[x]->red_name = expand(f_struct[i].red[x]->red_name, proc);
			x++;
		}
		i++;
	}
	ft_delete_all_qoutes(f_struct);
	free_func(f_struct->f_cmd);
	return (f_struct);
}
