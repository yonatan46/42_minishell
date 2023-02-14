/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:53:15 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/14 12:29:30 by yonamog2         ###   ########.fr       */
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

int	ft_del_qt_util(t_pars_var *var, t_pipe *f_struct, char *str)
{
	if (str[var->z] == '\'')
	{
		var->f = var->z;
		var->ch = ft_del_quotes(str, &var->z, '\'');
		var->ch1 = ft_substr(str, var->k, var->f);
		var->tmp = f_struct[var->i].arg[var->j];
		f_struct[var->i].arg[var->j] = ft_strjoin(var->ch1, var->ch);
		free(var->ch);
		free(var->ch1);
	}
	else if (str[var->z] == '\"')
	{
		var->f = var->z;
		var->ch = ft_del_quotes(str, &var->z, '\"');
		var->ch1 = ft_substr(str, var->k, var->f);
		var->tmp = f_struct[var->i].arg[var->j];
		f_struct[var->i].arg[var->j] = ft_strjoin(var->ch1, var->ch);
		free(var->ch);
		free(var->ch1);
	}
	if (str[var->z] == '\0')
		return (1);
	if (var->tmp)
		free(var->tmp);
	return (0);
}

void	ft_delete_argquotes(t_pipe *f_struct, char *str, int i, int j)
{
	t_pars_var	var;

	var.z = -1;
	var.k = 0;
	var.tmp = NULL;
	var.i = i;
	var.j = j;
	while (str[++var.z])
		if (ft_del_qt_util(&var, f_struct, str) == 1)
			break ;
	if (var.tmp)
		free(var.tmp);
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
			ft_delete_argquotes(f_struct, f_struct[i].arg[j], i, j);
	}
}

char	*ft_check_pipe_after_red(char *str)
{
	t_pars_var	var;
	int		check_quote;

	check_quote = 0;
	var.i = -1;
	var.j = 0;
	var.k = ft_calc_redpipe(str, '|');
	var.f = ft_strlen(str);
	var.tmp = (char *)malloc(sizeof(char) * (var.f - var.k + 1));
	while (str[++var.i])
	{
		ft_quote_zero_one(str[var.i], '|', &check_quote);
		if (str[var.i] == '|' && !(check_quote))
		{
			if (var.i >= 1 && str[var.i] == '|' && str[var.i - 1] == '>')
				var.tmp[var.j++] = str[++var.i];
			else
				var.tmp[var.j++] = str[var.i];
		}
		else
			var.tmp[var.j++] = str[var.i];
	}
	var.tmp[var.j] = '\0';
	return (var.tmp);
}


t_pipe	*ft_lexer(char *str, t_data	*proc)
{
	(void)proc;
	int		i;
	// int		x;
	char	**vars;
	int		pipes_num;
	t_pipe	*f_struct;

	i = 0;
	str = ft_check_pipe_after_red(str);
	str = ft_add_sp_redname(str);
	pipes_num = ft_calc(str, '|');
	vars = ft_clean_sp_struct(ft_separate_sp_pipe(str, '|'));
	f_struct = ft_calloc(sizeof(t_pipe), pipes_num + 2);
	while (vars[i])
	{
		f_struct[i].f_cmd = ft_separate_sp_pipe(vars[i], ' ');
		f_struct[i].cmd_len = pipes_num + 1;
		i++;
	}
	ft_count_struct(f_struct);

				/**
				 * to be changed!!!!!!!!!!
				*/
	// i = 0;
	// x = 0;
	// while (i < f_struct->cmd_len)
	// {
	// 	f_struct[i].cmd = expand(f_struct[i].cmd, proc);
	// 	// f_struct[i].cmd = expand_dollar_sign(f_struct[i].cmd);
		
	// 	x = 0;
	// 	while (f_struct[i].arg && f_struct[i].arg[x])
	// 	{
	// 		f_struct[i].arg[x] = expand(f_struct[i].arg[x], proc);
	// 		// f_struct[i].arg[x] = expand_dollar_sign(f_struct[i].arg[x]);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	while (x < f_struct[i].red_len)
	// 	{
	// 		f_struct[i].red[x]->red_sign = expand(f_struct[i].red[x]->red_sign, proc);
	// 		// f_struct[i].red[x]->red_sign = expand_dollar_sign(f_struct[i].red[x]->red_sign);
	// 		f_struct[i].red[x]->red_name = expand(f_struct[i].red[x]->red_name, proc);
	// 		// f_struct[i].red[x]->red_name = expand_dollar_sign(f_struct[i].red[x]->red_name);
	// 		x++;
	// 	}
	// 	i++;
	// }
	ft_delete_all_qoutes(f_struct);
	free_func(vars);
	if (str)
		free(str);
	return (f_struct);
}
