/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:42:18 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/15 18:05:16 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * replace_heredocs_util: main loop to replace the << with tmp file
 * @av:
 * @proc:
*/
int	replace_heredocs_util(t_pipe *av, int *x, int *y, t_heredoc_var *var)
{
	if (var->tmp == NULL)
	{
		if (var->tmp2)
			free(var->tmp2);
		g_err_code = 0;
		close(var->file1);
		return (1);
	}
	else if (ft_strcmp(var->tmp, var->tmp2) == 0)
	{
		if (var->tmp2)
			free(var->tmp2);
		free(av[*x].red[*y]->red_name);
		free(av[*x].red[*y]->red_sign);
		av[*x].red[*y]->red_name = ft_strdup(".var->tmp");
		av[*x].red[*y]->red_sign = ft_strdup("<");
		close(var->file1);
		free(var->tmp);
		return (2);
	}
	return (0);
}

/**
 * replace_heredocs: replace the << with tmp file
 * @av:
 * @proc:
*/
int	replace_heredocs(t_pipe *av, int *x, int *y, t_data *proc)
{
	t_heredoc_var	var;

	var.file1 = open(".tmp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (var.file1 == -1)
		terminate(av[proc->index].red[*x]->red_name, proc, av);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		var.tmp = get_next_line(0);
		var.tmp2 = ft_strjoin(av[*x].red[*y]->red_name, "\n");
		var.ret = replace_heredocs_util(av, x, y, &var);
		if (var.ret == 1)
			return (1);
		if (var.ret == 2)
			break ;
		simple_free(var.tmp2);
		write(var.file1, var.tmp, ft_strlen(var.tmp));
		simple_free(var.tmp);
	}
	if (var.tmp == NULL)
	{
		g_err_code = 0;
		return (close(var.file1), 1);
	}
	return (0);
}

/**
 * check_and_update_heredoc: check if there is heredoc and accept input
 * @av:
 * @proc:
*/
int	check_and_update_heredoc(t_pipe *av, t_data *proc)
{
	int		x;
	int		y;

	x = 0;
	while (x < av->cmd_len)
	{
		y = 0;
		while (y < av[x].red_len)
		{
			if (ft_strcmp(av[x].red[y]->red_sign, "<<") == 0)
				if (replace_heredocs(av, &x, &y, proc) == 1)
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}
