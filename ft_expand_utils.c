/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:41:59 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 12:25:36 by yonamog2         ###   ########.fr       */
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
		tmp = ft_substr(str, var->x - 1, 2);
		var->cp = ftt_strjoin(var->cp, tmp);
		free(tmp);
		var->x++;
	}
	else
	{
		tmp = ft_substr(str, var->x - 1, 1);
		var->cp = ftt_strjoin(var->cp, tmp);
		free(tmp);
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
		free(tmp);
		var->x++;
		return (1);
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
		while (str[var->x] != '$' && str[var->x] \
		!= ' ' && str[var->x] && str[var->x] != '\"' && \
		str[var->x] != '\'' && str[var->x] != '/' && \
		str[var->x] != '=' && str[var->x] != '\\')
			var->x++;
		get_env_and_replace(var, str);
	}
	return (0);
}
