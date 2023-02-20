/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:41:59 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/19 14:28:13 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * expand_util_2: check is the char is ? or ' ' then add it and return 1
 * @var: the struct containing vars
 * @str: is the raw input from the user
*/
static	void	expand_util_3(t_exp_var *var, char *str)
{
	char	*tmp;

	if (str[var->x] == '\"' || str[var->x] == ' ')
	{
		tmp = ft_substr(str, var->x, 2);
		var->cp = ftt_strjoin(var->cp, tmp);
		simple_free(tmp);
		var->x++;
	}
	else
	{
		tmp = ft_substr(str, var->x - 1, 1);
		var->cp = ftt_strjoin(var->cp, tmp);
		simple_free(tmp);
	}
	var->x++;
}

/**
 * expand_util_2: check is the char is ? or ' ' then add it and return 1
 * @var: the struct containing vars
 * @str: is the raw input from the user
*/
int	expand_util_2(t_exp_var *var, char *str)
{
	char	*tmp;

	if (str[var->x] == '?')
	{
		tmp = ft_itoa(g_err_code);
		var->cp = ftt_strjoin(var->cp, tmp);
		simple_free(tmp);
		var->x++;
		set_flag(var, str);
		return (1);
	}
	else if (str[var->x] == '$')
	{
		tmp = ft_itoa(getpid());
		var->cp = ftt_strjoin(var->cp, tmp);
		return (simple_free(tmp), var->x++, 1);
	}
	else if (str[var->x] == ' ')
	{
		var->cp = ftt_strjoin(var->cp, ft_substr(str, var->x - 1, 2));
		var->x++;
		return (1);
	}
	return (0);
}

/**
 * expand_util: a function that is removed from the main expand func
 * @var: the struct containing vars
 * @str: is the raw input from the user
*/
int	expand_util(t_exp_var *var, char *str)
{
	var->x++;
	if (var->flag_sq == 0)
	{
		if (expand_util_2(var, str) == 1)
			return (1);
		if (str[var->x] == ' ' || str[var->x] == '\0' || str[var->x] == '\"')
		{
			expand_util_3(var, str);
			return (1);
		}
		var->start = var->x;
		while (ft_isalnum(str[var->x]))
			var->x++;
		get_env_and_replace(var, str);
	}
	return (0);
}

/**
 * set_flag: just set flag based on the quote status
 * @var: the struture containing the variables for the expansion
 * @str: the string to be expanded from
*/
void	set_flag(t_exp_var *var, char *str)
{
	if (str[var->x] == '\'' && var->flag_dq == 0)
		var->flag_sq = !var->flag_sq;
	else if (str[var->x] == '\"' && var->flag_sq == 0)
		var->flag_dq = !var->flag_dq;
}

char	*expand_vars(char *str, t_data *proc)
{
	t_exp_var	var;

	var.x = 0;
	expand_init_vars(&var, proc);
	while (str[var.x])
	{
		if (str[var.x] != '$')
		{
			tool(str, &var);
			continue ;
		}
		var.start = var.x;
		if (expand_util_4(str, &var) == 1)
			break ;
		if (str[var.x] == '\0')
			break ;
	}
	free(str);
	return (var.cp);
}
