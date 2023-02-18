/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:53:15 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/18 15:38:25 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int			check_quote;

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
	int		i;
	char	**vars;
	int		pipes_num;
	t_pipe	*f_struct;

	i = 0;
	str = ft_check_pipe_after_red(str);
	str = ft_add_sp_redname(str);
	pipes_num = ft_calc(str, '|');
	vars = ft_c_sp_struct(ft_separate_sp_pipe(str, '|'));
	f_struct = ft_calloc(sizeof(t_pipe), pipes_num + 2);
	while (vars[i])
	{
		f_struct[i].f_cmd = ft_separate_sp_pipe(vars[i], ' ');
		f_struct[i].cmd_len = pipes_num + 1;
		f_struct[i].arg_len = 0;
		i++;
	}
	ft_count_struct(f_struct);
	expand_structs(f_struct, proc);
	ft_delete_all_qoutes(f_struct);
	free_func(vars);
	simple_free(str);
	return (f_struct);
}
