/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:07:29 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/19 14:28:26 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * get_env_and_replace: get the exanding value and put it to the string
 * @var: the struct containing vars
 * @str: is the raw input from the user
*/
void	get_env_and_replace(t_exp_var *var, char *str)
{	
	char	*tmp;

	tmp = ft_substr(str, var->start, var->x - var->start);
	var->tmp = ft_getenv(var->tmp_list, tmp);
	simple_free(tmp);
	if (var->tmp == NULL)
	{
		var->cp = ftt_strjoin(var->cp, var->tmp);
	}
	else
		var->cp = ftt_strjoin(var->cp, var->tmp);
}

/**
 * expand_init_vars: a function to initialize value of the strucutre
 * @var: the struct containing vars
*/
void	expand_init_vars(t_exp_var *var, t_data *proc)
{
	var->x = 0;
	var->start = 0;
	var->flag_sq = 0;
	var->flag_dq = 0;
	var->cp = NULL;
	var->tmp = NULL;
	var->tmp_list = *proc->head;
}

/**
 * tool: get the string,, join it with the mainm then simple_free tmp
*/

void	tool(char *str, t_exp_var *var)
{
	char		*tmp;

	tmp = ft_substr(str, var->x, 1);
	var->cp = ftt_strjoin(var->cp, tmp);
	simple_free(tmp);
	var->x++;
}

/***
 * expand_util_4: somthine
*/
int	expand_util_4(char *str, t_exp_var *var)
{
	if (str[var->x] != '$')
		tool(str, var);
	else if (str[var->x] == '$')
	{
		if (str[var->x + 1] == '\0')
		{
			var->tmp_ex = ft_substr(str, var->x, 1);
			var->cp = ftt_strjoin(var->cp, var->tmp_ex);
			return (simple_free(var->tmp_ex), 1);
		}
		else if (ft_isdigit(str[var->x + 1]) == 1)
		{
			var->x += 2;
		}
		else if (ft_isalpha(str[var->x + 1]) == 0 && \
		str[var->x + 1] != '?' && str[var->x + 1] != '$' \
		&& str[var->x + 1] != '\"' && str[var->x + 1] != '\'')
			tool(str, var);
		else
			expand_util(var, str);
	}
	return (0);
}

/**
 * expand: a simple function that update the string based on the  $,, simply
 * expands if there is anything with $
 * @str: is the raw input from the user
*/
char	*expand(char *str, t_data *proc)
{
	t_exp_var	var;

	if (str)
	{
		expand_init_vars(&var, proc);
		while (str[var.x])
		{
			set_flag(&var, str);
			if ((var.flag_sq == 1 || str[var.x] != '$'))
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
		return (simple_free(str), var.cp);
	}
	return (NULL);
}
