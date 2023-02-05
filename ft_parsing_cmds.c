/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:00:23 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/05 13:05:50 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * free_short: frr one string and 2d array
 * @path: the string to be freed
 * @path_split: the 2d array to be freed
*/
void	free_short(char *path, char **path_split)
{
	free(path);
	free_func(path_split);
}

/**
 * parsing_middle: parsing the middle command
 * @proc: the structure containing all info
 * @envp: the environment variable
 * @s: the command string
*/
char	*parsing_middle(t_data *proc, char **envp, char *s)
{
	proc->x = 0;
	if (search(envp) == 0)
		return (NULL);
	if (ft_strnstr(s, "/", ft_strlen(s)))
		return (s);
	while (!ft_strnstr(envp[proc->x], "PATH", 4))
		proc->x++;
	proc->path_split = ft_split(envp[proc->x] + 5, ':');
	proc->x = -1;
	while (proc->path_split[++proc->x] && (search(envp) == 1))
	{
		proc->path = ft_strjoin(proc->path_split[proc->x], "/");
		proc->result = ft_strjoin(proc->path, s);
		if (access(proc->result, 0) == 0)
		{
			free_short(proc->path, proc->path_split);
			return (proc->result);
		}
		if (proc->path)
			free(proc->path);
		free(proc->result);
	}
	return (free_short(NULL, proc->path_split), NULL);
}

void	init_parsing(t_data *proc)
{
	proc->x = -1;
	proc->t_lst = *proc->head;
	proc->path = NULL;
	proc->result = NULL;
}

/**
 * pars and check validity of command
*/
char	*parsing(t_data *proc, char **envp, char *s)
{
	init_parsing(proc);
	if (ft_strnstr(s, "/", ft_strlen(s)))
		return (s);
	if (search(envp) == 0)
		return (NULL);
	while (envp[++proc->x])
	{
		if (ft_strncmp(envp[proc->x], "PATH=", 5) == 0)
			break ;
	}
	proc->path_split = ft_split(envp[proc->x] + 5, ':');
	proc->x = -1;
	while (proc->path_split[++proc->x] && (search(envp) == 1))
	{
		proc->path = ft_strjoin(proc->path_split[proc->x], "/");
		proc->result = ft_strjoin(proc->path, s);
		if (access(proc->result, 0) == 0)
			return (free_short(proc->path, proc->path_split), proc->result);
		if (proc->path)
			free(proc->path);
		free(proc->result);
	}
	return (free_short(NULL, proc->path_split), NULL);
}
