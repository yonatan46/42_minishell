/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_del.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:52:32 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/05 15:59:38 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_all_qoutes(t_pipe *f_struct)
{
	ft_delete_redname_quotes(f_struct);
	ft_delete_cmd_quotes(f_struct);
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
			f_struct[*i].red[*j]->red_name = ft_strjoin(ch1, ch);
		}
		else if (str[z] == '\"')
		{
			f = z;
			ch = ft_del_quotes(str, &z, '\"');
			ch1 = ft_substr(str, k, f);
			f_struct[*i].red[*j]->red_name = ft_strjoin(ch1, ch);
		}
	}
}

void	ft_delete_cmd_quotes(t_pipe *f_struct)
{
	int	i;
	int	j;

	i = -1;
	while (f_struct[++i].cmd)
	{
		j = -1;
		while (f_struct[i].cmd[++j])
		{
			if (f_struct[i].cmd[j] == '\'')
				f_struct[i].cmd = ft_del_quotes(f_struct[i].cmd, &j, '\'');
			else if (f_struct[i].cmd[j] == '\"')
				f_struct[i].cmd = ft_del_quotes(f_struct[i].cmd, &j, '\"');
		}
	}
}

char	*ft_del_quotes(char *str, int *i, char c)
{
	int		j;
	int		count;
	int		count_quotes;
	char	*ch;

	j = 0;
	count_quotes = 0;
	count = ft_strlen(str);
	if (c == '\'')
		count_quotes = ft_count_quotes(str, '\'');
	else if (c == '\"')
		count_quotes = ft_count_quotes(str, '\"');
	count = count - count_quotes;
	ch = (char *)malloc(sizeof(char) * (count + 1));
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