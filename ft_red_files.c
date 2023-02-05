/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:09:42 by yonamog2          #+#    #+#             */
/*   Updated: 2023/01/23 19:27:14 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * first proc redirection
 * @av: the structure that contain the specific pipe
 * @flag: the output redirection flag
*/
void	red_first_proc(t_pipe *av, int *flag)
{
	int	x;

	x = 0;
	while (x < av->red_len)
	{
		if (strcmp(av->red[x]->red_sign, ">") == 0)
			*flag = red_output(av, x);
		else if (strcmp(av->red[x]->red_sign, "<") == 0)
			red_infile(av, x);
		else if (strcmp(av->red[x]->red_sign, ">>") == 0)
<<<<<<< HEAD:redirections.c
		{
			file1 = open(av->red[x]->red_name, O_RDWR | O_CREAT | O_APPEND, 0777);
			if (file1 == -1)
				terminate(av->red[x]->red_name);
			*flag = 1;
			dup2(file1, STDOUT_FILENO);
			close(file1);
		}
=======
			*flag = red_append_mode(av, x);
>>>>>>> 13e1b799c82fd8601878275121dd598ee2bc5a74:ft_red_files.c
		x++;
	}
}

/**
 * red_one_cmd-> redirection for middle command
 * @av: the structure that contain the specific pipe
*/
void	red_one_cmd(t_pipe *av)
{
	int	x;

	x = 0;
	while (x < av->red_len)
	{
		if (strcmp(av->red[x]->red_sign, ">") == 0)
			red_output(av, x);
		else if (strcmp(av->red[x]->red_sign, "<") == 0)
			red_infile(av, x);
		else if (strcmp(av->red[x]->red_sign, ">>") == 0)
			red_append_mode(av, x);
		x++;
	}
}
/**
 * red_middle-> redirection for middle command
 * @av: the structure that contain the specific pipe
 * @flag_out: the flag to check output redirection
 * @flag_in: the flag to check input redirection
*/

void	red_middle(t_pipe *av, int *flag_out, int *flag_in)
{
	int	x;

	x = -1;
	while (++x < av->red_len)
	{
		if (strcmp(av->red[x]->red_sign, ">") == 0)
			*flag_out = red_output(av, x);
		else if (strcmp(av->red[x]->red_sign, "<") == 0)
			*flag_in = red_infile(av, x);
		else if (strcmp(av->red[x]->red_sign, ">>") == 0)
<<<<<<< HEAD:redirections.c
		{
			file1 = open(av->red[x]->red_name, O_RDWR | O_CREAT | O_APPEND, 0777);
			if (file1 == -1)
				terminate(av->red[x]->red_name);
			*flag_out = 1;
			dup2(file1, STDOUT_FILENO);
			close(file1);
		}
=======
			*flag_out = red_append_mode(av, x);
>>>>>>> 13e1b799c82fd8601878275121dd598ee2bc5a74:ft_red_files.c
	}
}

/**
 * redirection for the last command
 * @av: the structure that contain the specific pipe
 * @flag: the flag to check if we redirect to a file or not
 * or itll stay in the default
*/
void	red_last_proc(t_pipe *av, int *flag)
{
	int	x;

	x = -1;
	while (++x < av->red_len)
	{
		if (strcmp(av->red[x]->red_sign, ">") == 0)
			red_output(av, x);
		else if (strcmp(av->red[x]->red_sign, "<") == 0)
			*flag = red_infile(av, x);
		else if (strcmp(av->red[x]->red_sign, ">>") == 0)
<<<<<<< HEAD:redirections.c
		{
			file1 = open(av->red[x]->red_name, O_RDWR | O_CREAT | O_APPEND, 0777);
			if (file1 == -1)
				terminate(av->red[x]->red_name);
			dup2(file1, STDOUT_FILENO);
			close(file1);
		}
=======
			red_append_mode(av, x);
>>>>>>> 13e1b799c82fd8601878275121dd598ee2bc5a74:ft_red_files.c
	}
}
