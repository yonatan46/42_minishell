/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:48:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/04 22:41:07 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_exp_var *var)
{
	var->flag_pwd = 0;
	var->x = 0;
	var->y = 0;
	var->flag_shlvl = 0;
	var->flag_oldpwd = 0;
}

int	ft_linked_env_util_2(t_exp_var *var, t_list *head, \
t_data *proc, char **env)
{
	if (ft_strncmp(env[var->x], "PWD=", 4) == 0)
	{
		var->flag_pwd = 1;
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("PWD="), \
		getcwd(proc->pwd, 1024), var->x, var->x));
		var->x++;
		return (1);
	}
	else if (ft_strncmp(env[var->x], "SHLVL=", 6) == 0)
	{
		var->flag_shlvl = 1;
		ft_lstadd_back(&head, ft_lstnew(ft_substr(env[var->x], 0, var->y + 1), \
		ft_itoa(ft_atoi(ft_substr(env[var->x], var->y + 1, \
		ft_strlen(env[var->x]) - var->y)) + 1), var->x, var->x));
		var->x++;
		return (1);
	}
	return (0);
}

int	ft_linked_env_util(t_exp_var *var, t_list *head, t_data *proc, char **env)
{
	if (ft_linked_env_util_2(var, head, proc, env) == 1)
		return (1);
	else if (ft_strncmp(env[var->x], "OLDPWD=", 7) == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("OLDPWD="), \
		ft_strdup(ft_substr(env[var->x], var->y + 1, \
		ft_strlen(env[var->x]) - var->y)), var->x, var->x));
		var->x++;
		var->flag_oldpwd = 1;
		return (1);
	}
	else if (ft_strncmp(env[var->x], "_=", 2) == 0)
	{
		var->x++;
		return (1);
	}
	return (0);
}

void	check_and_set(t_exp_var *var, t_list *head, t_data *proc)
{
	if (var->flag_pwd == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("PWD="), \
		getcwd(proc->pwd, 1024), var->x, var->x));
		var->x++;
	}
	if (var->flag_shlvl == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("SHLVL="), \
		ft_strdup("1"), var->x, var->x));
		var->x++;
	}
	if (var->flag_oldpwd == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("OLDPWD"), \
		NULL, var->x, var->x));
		var->x++;
	}
}

/**
 * ft_linked_env: creates a copy of the environment
 *  variable we get but in linked list form
 * @proc: the struct that contains all the variables
 * @env: the environment variable
*/
void	ft_linked_env(t_data *proc, char **env)
{
	t_list		*head;
	t_exp_var	var;

	init_vars(&var);
	head = NULL;
	while (env[var.x])
	{
		if (ft_strchr(env[var.x], '='))
		{
			var.y = 0;
			while (env[var.x][var.y] && env[var.x][var.y] != '=')
				var.y++;
		}
		if (ft_linked_env_util(&var, head, proc, env) == 1)
			continue ;
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(\
		ft_substr(env[var.x], 0, var.y + 1)), \
		ft_strdup(ft_substr(env[var.x], var.y + 1, \
		ft_strlen(env[var.x]) - var.y)), var.x, var.x));
		var.x++;
	}
	check_and_set(&var, head, proc);
	proc->head = malloc(sizeof(t_list *));
	*proc->head = head;
}

/**
 * ft_env_print_linked: is a function that simply prints the env
 * @proc: is a structure that contains all variables plus 
 * the head to the linked list
*/
void	ft_env_print_linked(t_data *proc)
{
	t_list	*tmp;

	tmp = *proc->head;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '='))
			printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	exit(0);
}

/**
 * count_till_equl_sign: just a function that scan and count until = sign
 * @str: the string to be searched
*/
int	compare_until_eq(char *str1, char *str2)
{
	int	x;

	x = 0;
	while ((str1[x] && str1[x] != '=') && (str2[x] && str2[x] != '='))
	{
		if (str1[x] != str2[x])
			return (str1[x] - str2[x]);
		x++;
	}
	if ((str1[x] == '\0' && str2[x] == '\0') || \
	(str1[x] == '=' && str2[x] == '='))
		return (0);
	return (1);
}

int	chek_exp_a_rplc_util(t_exp_var *var, char *replace)
{
	while (var->tmp_list)
	{
		if (compare_until_eq(var->tmp_list->key, replace) == 0)
		{
			if (ft_strchr(replace, '='))
			{
				var->y = 0;
				while (replace[var->y] && replace[var->y] != '=')
					var->y++;
				var->tmp_list->key = ft_substr(replace, 0, var->y + 1);
				var->tmp_list->value = ft_substr(replace, var->y + 1, \
				ft_strlen(replace) - var->y);
			}
			var->flag = 1;
			return (1);
		}
		var->last_index = var->tmp_list->index;
		var->last_pos = var->tmp_list->position;
		var->tmp_list = var->tmp_list->next;
	}
	return (0);
}

int	chek_exp_a_rplc(t_list *head, char *replace)
{
	t_exp_var	var;

	var.tmp_list = head;
	var.flag = 0;
	if (chek_exp_a_rplc_util(&var, replace) == 1)
		return (0);
	if (var.flag == 0)
	{
		var.y = 0;
		while (replace[var.y] && replace[var.y] != '=')
			var.y++;
		ft_lstadd_back(&head, ft_lstnew(ft_substr(replace, 0, var.y + 1), \
		ft_substr(replace, var.y + 1, ft_strlen(replace)), \
		var.last_index + 1, var.last_pos + 1));
	}
	return (0);
}

int	ft_validate_exprot(char *str)
{
	int	x;

	x = 0;
	if (ft_isalpha(str[0]) == 1 || str[0] == '_')
	{
		while (str[x] && str[x] != '=')
		{
			if (str[x] == '_' || ft_isalnum(str[x]) == 1)
				x++;
			else
				return (1);
		}
		return (0);
	}
	return (1);
}

void	print_and_set_flag(t_pipe *pipe, t_data *proc)
{
	write(1, "`", 1);
	write(1, pipe->arg[proc->x], ft_strlen(pipe->arg[proc->x]));
	write(1, "'", 1);
	ft_putstr_fd(": not a valid identifier\n", 2);
	proc->flag = 1;
}
/**
 * ft_export_print_linked: is a function that does export like bash
 * it basically take the linked list and print it in sorted order
 * @sort_list: is a function that sort linked list
 * @proc: is a structure that contains all variables plus the 
 * head to the linked list
*/

int	ft_export_print_linked(t_pipe *pipe, t_data *prc)
{
	prc->flag = 0;
	prc->t_lst = *prc->head;
	prc->x = 0;
	if (pipe->arg[1])
	{
		while (pipe->arg[++prc->x])
		{
			if (ft_validate_exprot(pipe->arg[prc->x]) == 1)
				print_and_set_flag(pipe, prc);
			else
				chek_exp_a_rplc(*prc->head, pipe->arg[prc->x]);
		}
		return (prc->flag);
	}
	sort_list(*prc->head);
	prc->t_lst = *prc->head;
	while (prc->t_lst)
	{
		if (ft_strchr(prc->t_lst->key, '='))
			printf("declare -x %s\"%s\"\n", prc->t_lst->key, prc->t_lst->value);
		else
			printf("declare -x %s\n", prc->t_lst->key);
		prc->t_lst = prc->t_lst->next;
	}
	return (0);
}

/**
 * ft_export: print the environment variables from the saved 
 * env 2d array but formatted
 * @env: the 2d array containing the enviroment variables
 * just take the env and print it comapiring the 
 * variables based on their letters
 * makes it easier
*/
void	ft_export(char **str)
{
	int	size;

	size = 0;
	while (str[size])
	{
		printf("declareeee -x %s\n", str[size]);
		size++;
	}
	exit(0);
}

/**
 * ft_env: print the environment variables from the saved env 2d array
 * @env: the 2d array containing the enviroment variables
*/

void	ft_env(char **env)
{
	int	x;

	x = 0;
	while (env[x])
		printf("%s\n", env[x++]);
}

int	ft_unset_check_and_unset(t_list **main_head, \
char **args)
{
	int		x;
	t_list	*tmp;

	x = -1;
	while (args[++x])
	{
		if (ft_strchr(args[x], '='))
			return (1);
		tmp = *main_head;
		while (tmp)
		{
			if (strncmp(tmp->key, args[x], \
			ft_strlen(tmp->key) - 1) == 0)
			{
				remove_element(main_head, tmp->index);
				return (0);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

/**
 * ft_unset: remove from env variables
*/
int	ft_unset(t_pipe *pipe, t_data *proc)
{
	int	x;
	int	res;

	x = 0;
	res = 0;
	if (pipe->arg[1])
		while (pipe->arg[++x])
			res = ft_unset_check_and_unset(proc->head, &pipe->arg[x]);
	return (res);
}
