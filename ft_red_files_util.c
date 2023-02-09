/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_files_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:48:29 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/09 16:00:10 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * red_output: a function that redirects output
 * @av: the structure containing the cmds and redirections
 * @x: the index of the redirection
*/
int	red_output(t_pipe *av, int x, t_data *proc)
{
	int	file1;

	file1 = open(av[proc->index]. red[x]->red_name,
			O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file1 == -1)
		terminate(av[proc->index].red[x]->red_name, proc, av);
	dup2(file1, STDOUT_FILENO);
	close(file1);
	return (1);
}

/**
 * red_infile: a function that redirects input
 * @av: the structure containing the cmds and redirections
 * @x: the index of the redirection
*/
int	red_infile(t_pipe *av, int x, t_data *proc)
{
	int	file1;

	file1 = open(av[proc->index].red[x]->red_name, O_RDONLY);
	if (file1 == -1)
		terminate(av[proc->index].red[x]->red_name, proc, av);
	dup2(file1, STDIN_FILENO);
	close(file1);
	return (1);
}

/**
 * red_append_mode: a function that redirects output in appaned mode
 * @av: the structure containing the cmds and redirections
 * @x: the index of the redirection
*/
int	red_append_mode(t_pipe *av, int x, t_data *proc)
{
	int	file1;

	file1 = open(av[proc->index].red[x]->red_name, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (file1 == -1)
		terminate(av[proc->index].red[x]->red_name, proc, av);
	dup2(file1, STDOUT_FILENO);
	close(file1);
	return (1);
}

int	replace_heredocs(t_pipe *av, int *x, int *y, t_data *proc)
{
	int		file1;
	char	*tmp;

	// signal(SIGINT, SIG_IGN);
	file1 = open(".tmp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (file1 == -1)
		terminate(av[proc->index].red[*x]->red_name, proc, av);
	tmp = get_next_line(0);
	if (tmp == NULL)
	{
		g_err_code = 0;
		close(file1);
		return (1);
	}
	while (tmp)
	{
		if (tmp == NULL)
		{
			g_err_code = 0;
			close(file1);
			return (1);
		}
		else if (strcmp(tmp, ft_strjoin(av[*x].red[*y]->red_name, "\n")) == 0)
		{
			free(av[*x].red[*y]->red_name);
			free(av[*x].red[*y]->red_sign);
			av[*x].red[*y]->red_name = ft_strdup(".tmp");
			av[*x].red[*y]->red_sign = ft_strdup("<");
			close(file1);
			free(tmp);
			break ;
			// return (1);
		}
		write(file1, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	return(0);
}

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
			if (strcmp(av[x].red[y]->red_sign, "<<") == 0)
				if(replace_heredocs(av, &x, &y, proc) == 1)
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}
