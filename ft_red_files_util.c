/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_files_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 12:48:29 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/05 19:58:21 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * red_output: a function that redirects output
 * @av: the structure containing the cmds and redirections
 * @x: the index of the redirection
*/
int	red_output(t_pipe *av, int x)
{
	int	file1;

	file1 = open(av->red[x]->red_name,
			O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file1 == -1)
		terminate(av->red[x]->red_name);
	dup2(file1, STDOUT_FILENO);
	close(file1);
	return (1);
}

/**
 * red_infile: a function that redirects input
 * @av: the structure containing the cmds and redirections
 * @x: the index of the redirection
*/
int	red_infile(t_pipe *av, int x)
{
	int	file1;

	file1 = open(av->red[x]->red_name, O_RDONLY);
	if (file1 == -1)
		terminate(av->red[x]->red_name);
	dup2(file1, STDIN_FILENO);
	close(file1);
	return (1);
}

/**
 * red_append_mode: a function that redirects output in appaned mode
 * @av: the structure containing the cmds and redirections
 * @x: the index of the redirection
*/
int	red_append_mode(t_pipe *av, int x)
{
	int	file1;

	file1 = open(av->red[x]->red_name, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (file1 == -1)
		terminate(av->red[x]->red_name);
	dup2(file1, STDOUT_FILENO);
	close(file1);
	return (1);
}

void	replace_heredocs(t_pipe *av, int *x, int *y)
{
	int		file1;
	char	*tmp;

	signal(SIGINT, SIG_IGN);
	file1 = open(".tmp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (file1 == -1)
		terminate(av->red[*x]->red_name);
	tmp = get_next_line(0);
	while (tmp)
	{
		if (tmp == NULL)
		{
			g_err_code = 0;
			close(file1);
			break ;
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
		}
		write(file1, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
}

void	check_and_update_heredoc(t_pipe *av)
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
				replace_heredocs(av, &x, &y);
			y++;
		}
		x++;
	}
}
