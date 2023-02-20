/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_del.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:01:48 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/20 15:54:00 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_all_qoutes(t_pipe *f_struct)
{
	ft_delete_redname_quotes(f_struct);
	ft_delete_cmd_quotes_two(f_struct);
	ft_delete_arg_quotes(f_struct);
}

void	ft_delete_redname_quotes(t_pipe *f_struct)
{
	int		i;
	int		j;

	i = -1;
	while (++i < f_struct->cmd_len)
	{
		j = -1;
		if (f_struct[i].red_len > 0)
		{
			while (f_struct[i].red[++j])
				ft_copy_redname(f_struct, f_struct[i].red[j]->red_name, &i, &j);
		}
	}
}

void	ft_copy_redname(t_pipe *f_struct, char *str, int *i, int *j)
{
	t_pars_var	var;

	var.z = -1;
	while (str[++var.z])
	{
		var.f = var.z;
		if (str[var.z] == '\'')
		{
			var.ch = ft_del_quotes(str, &var.z, '\'');
			var.ch1 = ft_substr(str, 0, var.f);
			simple_free(f_struct[*i].red[*j]->red_name);
			f_struct[*i].red[*j]->red_name = ft_strjoin(var.ch1, var.ch);
			simple_free(var.ch);
			simple_free(var.ch1);
		}
		else if (str[var.z] == '\"')
		{
			var.ch = ft_del_quotes(str, &var.z, '\"');
			var.ch1 = ft_substr(str, 0, var.f);
			simple_free(f_struct[*i].red[*j]->red_name);
			f_struct[*i].red[*j]->red_name = ft_strjoin(var.ch1, var.ch);
			simple_free(var.ch);
			simple_free(var.ch1);
		}
		if ((int)ft_strlen(f_struct[*i].red[*j]->red_name) < var.z || str[var.z] == '\0')
			break ;
	}
}

void	ft_delete_cmd_quotes_two(t_pipe *f_struct)
{
	int	i;

	i = -1;
	while (f_struct[++i].cmd)
	{
		if (f_struct[i].cmd != NULL)
		{
			f_struct[i].cmd = ft_del_quotes_two(f_struct[i].cmd, '\'');
			f_struct[i].cmd = ft_del_quotes_two(f_struct[i].cmd, '\"');
		}
	}
}

char	*ft_del_quotes_two(char *str, char c)
{
	int		i;
	int		j;
	int		count;
	int		count_quotes;
	char	*ch;

	i = -1;
	j = 0;
	count_quotes = 0;
	count = 0;
	count = ft_strlen(str);
	if (c == '\'')
		count_quotes = ft_count_quotes(str, '\'');
	else if (c == '\"')
		count_quotes = ft_count_quotes(str, '\"');
	count = count - count_quotes;
	ch = (char *)malloc(sizeof(char) * (count + 1));
	while (str[++i])
	{
		if (str[i] != c)
			ch[j++] = str[i];
	}
	ch[j] = '\0';
	simple_free(str);
	return (ch);
}
