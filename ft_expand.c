/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:07:29 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/12 14:46:23 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * get_env_and_replace: get the exanding value and put it to the string
 * @var: the struct containing vars
 * @str: is the raw input from the user
*/
void	get_env_and_replace(t_exp_var *var, char *str)
{	
	char	*tmp;

	tmp = ft_substr(str, var->start, var->x - var->start);
	var->tmp = ft_getenv(var->tmp_list, tmp);
	free(tmp);
	if (var->tmp == NULL)
		var->cp = ftt_strjoin(var->cp, "");
	else
	{
		var->cp = ftt_strjoin(var->cp, var->tmp);
	}
}

/**
 * expand_util: a function that is removed from the main expand func
 * @var: the struct containing vars
 * @str: is the raw input from the user
*/
int	expand_util(t_exp_var *var, char *str)
{
	char	*tmp;

	var->x++;
	// printf("val : %c\n", str[var->x]);
	if (var->flag_sq == 0 || var->flag_dq == 1)
	{
		if (expand_util_2(var, str) == 1)
			return (1);
		if (str[var->x] == ' ' || str[var->x] == '\0' || str[var->x] == '\"')
		{
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
			return (1);
		}
		var->start = var->x;
		while (str[var->x] != '$' && str[var->x] \
		!= ' ' && str[var->x] && str[var->x] != '\"'  && str[var->x] != '\'' && str[var->x] != '/' && str[var->x] != '=' && str[var->x] != '\\')
			var->x++;
		get_env_and_replace(var, str);
	}
	return (0);
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
 * expand: a simple function that update the string based on the  $,, simply
 * expands if there is anything with $
 * @str: is the raw input from the user
*/
char	*expand(char *str, t_data *proc)
{
	t_exp_var	var;
	char		*tmp;

	if (str)
	{
		expand_init_vars(&var, proc);
		while (str[var.x])
		{
			if (str[var.x] == '\'')
				var.flag_sq = !var.flag_sq;
			if (str[var.x] == '\"')
				var.flag_dq = !var.flag_dq;
			if (var.flag_sq == 1 && var.flag_dq == 0)
			{
				tmp = ft_substr(str, var.x, 1);
				var.cp = ftt_strjoin(var.cp, tmp);
				free(tmp);
				var.x++;
				continue ;
			}
			var.start = var.x;
			if (str[var.x] != '$')
			{
				tmp = ft_substr(str, var.x, 1);
				var.cp = ftt_strjoin(var.cp, tmp);
				free(tmp);
				var.x++;
			}
			else if (str[var.x] == '$')
			{
				if (str[var.x + 1] == '\0')
				{
					tmp = ft_substr(str, var.x, 1);
					var.cp = ftt_strjoin(var.cp, tmp);
					free(tmp);
					break ;
				}
				else if (ft_isdigit(str[var.x + 1]) == 1)
					var.x += 2;
				else if (ft_isalpha(str[var.x + 1]) == 0 && str[var.x + 1] != '?')
				{
					tmp = ft_substr(str, var.x, 1);
					var.cp = ftt_strjoin(var.cp, tmp);
					free(tmp);
					var.x++;
				}
				else
					expand_util(&var, str);
			}
			if (str[var.x] == '\0')
				break ;
		}
		free(str);
		return (var.cp);
	}
	return (NULL);
}
