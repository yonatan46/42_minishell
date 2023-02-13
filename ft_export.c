/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:48:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 19:59:34 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * ft_export_print_linked: is a function that does export like bash
 * it basically take the linked list and print it in sorted order
 * @sort_list: is a function that sort linked list
 * @proc: is a structure that contains all variables plus the 
 * head to the linked list
*/

int	ft_export_print_linked(t_pipe *pipe, t_data *prc)
{
	sort_list(*prc->head);
	re_index(*prc->head);
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

int	ft_unset_check_and_unset(t_list **main_head, \
char **args)
{
	int		x;
	t_list	*tmp;
	char	*tmp_copy;

	x = -1;
	while (args[++x])
	{
		if (ft_strchr(args[x], '='))
		{
			write(2, args[x], ft_strlen(args[x]));
			ft_putstr_fd(" : not a valid identifier\n", 2);
			return (1);
		}
		tmp = *main_head;
		while (tmp)
		{
			tmp_copy = ft_strjoin(args[x], "=");
			if (strcmp(tmp->key, tmp_copy) == 0)
			{
				if (tmp_copy)
					free(tmp_copy);
				remove_element(main_head, tmp->index);
				return (0);
			}
			if (tmp_copy)
				free(tmp_copy);
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
