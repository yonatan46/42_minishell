/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   added.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:03:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/01/30 18:30:07 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
/**
 * free_func: a function that free 2d array
 * @args: 2d array to be freed
*/
void	free_func(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}

/**
 * free_func_one_cmd: a function that free 2d array
 * @args: 2d array to be freed
*/
void	free_func_one_cmd(t_pipe *av)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (av->arg[size])
		size++;
	while (i < size)
		free(av->arg[i++]);
	free(av->arg);
	if(av->cmd[ft_strlen(av->cmd) -1] == '/')
	{
		write(2, av->cmd, ft_strlen(av->cmd));
		write(2, ": Is a directory\n", 18);
		exit(126);
	}
	write(2, av->cmd, ft_strlen(av->cmd));
	perror(" ");
	exit(126);
}

/**
 * terminate: a function that print error 
 *	@m: the string to dispplay before 
*/

void	terminate(char *m)
{
	perror(m);
	exit(1);
}

/**
 * cmd_not_found: a function that prints command not found and exit with 127 code
 * @res: a 2d array which contains the string name to be printed
*/
void	cmd_not_found(t_pipe *av)
{
	write(2, av->cmd, ft_strlen(av->cmd));
	write(2, ": command not found\n", 21);
	free_func(av->arg);
	exit(127);
}

