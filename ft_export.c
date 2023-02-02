/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:48:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/02 10:29:17 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_linked_env: creates a copy of the environment
 *  variable we get but in linked list form
 * @proc: the struct that contains all the variables
 * @env: the environment variable
*/
void ft_linked_env(t_data *proc, char **env)
{
	(void)proc;
	t_list *head = NULL;
	int x = 0;
	int y = 0;
	int flag_pwd = 0;
	int flag_shlvl = 0;
	int flag_oldpwd = 0;
	while (env[x])
	{
		if(ft_strchr(env[x] , '='))
		{
			y = 0;
			while (env[x][y] && env[x][y] != '=')
				y++;
		}
		if (ft_strncmp(env[x], "PWD=", 4) == 0)
		{
			flag_pwd = 1;
			ft_lstadd_back(&head, ft_lstnew(ft_strdup("PWD="), getcwd(proc->pwd, 1024), x, x));
			x++;
			continue ;
		}
		else if (ft_strncmp(env[x], "SHLVL=", 6) == 0)
		{
			flag_shlvl = 1;
			ft_lstadd_back(&head, ft_lstnew(ft_substr(env[x], 0, y + 1) ,\
			ft_itoa(ft_atoi(ft_substr(env[x], y + 1, ft_strlen(env[x]) - y)) + 1), x, x));
			x++;
			continue ;
		}
		else if (ft_strncmp(env[x], "OLDPWD=", 7) == 0)
		{
			ft_lstadd_back(&head, ft_lstnew(ft_strdup("OLDPWD="), \
			ft_strdup(ft_substr(env[x], y + 1, ft_strlen(env[x]) - y)), x, x));
			x++;
			flag_oldpwd  = 1;
			continue ;
		}
		else if (ft_strncmp(env[x], "_=", 2) == 0)
		{
			x++;
			continue ;
		}
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(ft_substr(env[x], 0, y + 1)), \
		ft_strdup(ft_substr(env[x], y + 1, ft_strlen(env[x]) - y)), x, x));
		x++;
	}
	// if (*proc->head == NULL)
	// {
	// 		ft_lstadd_back(&head, ft_lstnew(ft_strdup("PWD="), getcwd(proc->pwd, 1024), x, x));
	// 		x++;
	// 		ft_lstadd_back(&head, ft_lstnew(ft_strdup("SHLVL="), ft_strdup("1"), x, x));
	// 		x++;
	// 		ft_lstadd_back(&head, ft_lstnew(ft_strdup("OLDPWD="), ft_strdup(""), x, x));
	// 		flag_shlvl = 1;
	// 		flag_pwd = 1;
	// }
	if (flag_pwd == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("PWD="), getcwd(proc->pwd, 1024), x, x));
		x++;
	}
	if (flag_shlvl == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("SHLVL="), ft_strdup("1"), x, x));
		x++;
	}
	if (flag_oldpwd == 0)
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strdup("OLDPWD="), ft_strdup(""), x, x));
		x++;
	}
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
		if (ft_strchr(tmp->content, '=') )
		{
			printf("%s%s\n", tmp->content, tmp->value);
		}
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
	if (str1[x] == '\0' && str2[x] == '\0')
		return(0);
	return (1);
}
void	check_export_and_replace(t_list *head, char *replace)
{
	t_list	*tmp;
	int		y;
	int		last_index;
	int		last_pos;
	int		flag;

	tmp = head;
	flag = 0;
	while (tmp)
	{
		if (compare_until_eq(tmp->content, replace) == 0)
		{
			if (ft_strchr(replace, '='))
			{
				y = 0;
				while (replace[y] && replace[y] != '=')
					y++;
				tmp->content = ft_substr(replace, 0, y + 1);
				tmp->value = ft_substr(replace, y + 1, ft_strlen(replace) - y);
			}
			flag = 1;
			return ;
		}
		last_index = tmp->index;
		last_pos = tmp->position;
		tmp = tmp->next;
	}
	if (flag == 0)
	{
		y = 0;
		while (replace[y] && replace[y] != '=')
			y++;
		ft_lstadd_back(&head, ft_lstnew(ft_substr(replace, 0, y + 1), \
		ft_substr(replace, y + 1, ft_strlen(replace)), last_index + 1, last_pos + 1));
	}
	
}

int ft_validate_exprot(char *str)
{
	int x;

	x = 0;
	if (ft_isalpha(str[0]) == 1 || str[0] == '_')
	{
		while (str[x] && str[x] != '=')
		{
			if (str[x] == '_' || ft_isalnum(str[x]) == 1)
				x++;
			else
				return(1);	
		}
		return(0);
	}
	return(1);
}

/**
 * ft_export_print_linked: is a function that does export like bash
 * it basically take the linked list and print it in sorted order
 * @sort_list: is a function that sort linked list
 * @proc: is a structure that contains all variables plus the 
 * head to the linked list
*/

int	ft_export_print_linked(t_pipe *pipe, t_data *proc)
{
	int res;

	res = 0;
	proc->tmp_list = *proc->head;
	proc->x = 0;
	if (pipe->arg[1])
	{
		while (pipe->arg[++proc->x])
		{
			if (ft_validate_exprot(pipe->arg[proc->x]) == 1)
			{
				printf("`%s' : not a valid identifier\n", pipe->arg[proc->x]);
				res = 1;
			}
			else	
				check_export_and_replace(*proc->head, pipe->arg[proc->x]);
		}
		return (res);
	}
	sort_list(*proc->head);
	proc->tmp_list = *proc->head;
	while (proc->tmp_list)
	{
		if (ft_strchr(proc->tmp_list->content, '='))
			printf("declare -x %s\"%s\"\n", proc->tmp_list->content, proc->tmp_list->value);
		else
			printf("declare -x %s\n", proc->tmp_list->content);
		proc->tmp_list = proc->tmp_list->next;
	}
	return(0);
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

void	ft_unset_check_and_unset(t_list **main_head, \
char **args)
{
	int		x;
	t_list	*tmp;

	x = -1;
	while (args[++x])
	{
		if (ft_strchr(args[x], '='))
		{
			printf("%s: not a valid identifier\n", args[x]);
			return ;
		}
		tmp = *main_head;
		while (tmp)
		{
			if (strncmp(tmp->content, args[x], \
			ft_strlen(tmp->content) - 1) == 0)
			{
				remove_element(main_head, tmp->index);
				return ;
			}
			tmp = tmp->next;
		}
	}
}

/**
 * ft_unset: remove from env variables
*/
void	ft_unset(t_pipe *pipe, t_data *proc)
{
	if (pipe->arg[1])
	{
		printf("unset from exprot %s\n",pipe->arg[1]);
		ft_unset_check_and_unset(proc->head, &pipe->arg[1]);
	}
}
