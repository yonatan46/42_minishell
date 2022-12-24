/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:43:37 by yonamog2          #+#    #+#             */
/*   Updated: 2022/12/24 13:39:35 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	search(char **envp)
{
	int	x;

	x = -1;
	while (envp[++x])
		if (strnstr(envp[x], "PATH", 4) == NULL)
			return (1);
	return (0);
}

void	free_short(char *path, char **path_split)
{
	free(path);
	free_func(path_split);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	char	*str;
	int		x;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	x = -1;
	y = 0;
	str = malloc(sizeof(char) * (size1 + size2) + 1);
	if (!str)
		return (NULL);
	while (s1[++x] != '\0')
		str[x] = s1[x];
	while (s2[y] != '\0')
		str[x++] = s2[y++];
	str[x] = '\0';
	return (str);
}

char	*parsing(t_data *proc, char **envp, char *s)
{
	char	*path;
	char	**path_split;

	proc->x = 0;
	if (search(envp) == 0)
		return (NULL);
	if (strnstr(s, "/", ft_strlen(s)))
		return (s);
	while (!strnstr(envp[proc->x], "PATH", 4))
		proc->x++;
	path_split = ft_split(envp[proc->x] + 5, ':');
	proc->x = -1;
	while (path_split[++proc->x] && (search(envp) == 1))
	{
		path = ft_strjoin(path_split[proc->x], "/");
		proc->result = ft_strjoin(path, s);
		if (access(proc->result, 0) == 0)
		{
			free_short(path, path_split);
			return (proc->result);
		}
		free(proc->result);
	}
	free_short(path, path_split);
	return (NULL);
}

void handl(int num)
{
	return ;
}
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_data vars;

	signal(SIGINT, handl);
	signal(SIGSEGV, handl);
	signal(SIGABRT, handl);
	signal(SIGHUP, handl);
	signal(SIGPIPE, handl);
	signal(SIGTSTP, handl);
	while (1)
	{
		char *str = readline("minishell:> ");
		if (strcmp(str, "exit") == 0)
			exit(0);
		add_history (str);
		vars.res = ft_split(str, ' ');
		parsing(&vars, env, vars.res[0]);
		vars.res[0] = vars.result;
		// printf("%s\n", vars.res[0]);
		// printf("%s", vars.result);
		// char **done = ft_split(str, ' ');
		// int x = 0;
		// while (vars.res[x])
		// 	printf("%s\n", vars.res[x++]);
		int id = fork();
		if (id == 0)
			if(execve(vars.res[0], vars.res, env) == -1)
				perror("error ");
		wait(0);
		free(str);
	}
	return(0);
}