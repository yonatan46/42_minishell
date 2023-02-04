/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:00:54 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/04 21:34:49 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_loop_space(char *str, int *i)
{
	int	count;

	count = 0;
	while (ft_isspace(str[++(*i)]))
		count++;
	if (count == 0)
		return (1);
	return (0);
}

int	ft_check_red_pipe(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '>')
		{
			if (!ft_check_loop_space(str, &i))
				if (str[i] == '|')
					return (1);
		}
		else if (str[i] == '<')
		{
			ft_check_loop_space(str, &i);
			if (str[i] == '|')
				return (1);
		}
	}
	return (0);
}

int	ft_preparsing(char *str)
{
	int		i;
	int		check_quote;
	char	ch;

	check_quote = 0;
	i = 0;
	while ((ft_isspace(str[i])))
		i++;
	if (str[i] == '|' || str[i] == ';')
		return (1);
	if (ft_check_qoutes(str))
		return (1);
	if (ft_check_red_pipe(str))
		return (1);
	i = -1;
	while (str[++i])
	{
		if (!check_quote || ch == str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				ch = str[i];
				check_quote = !check_quote;
			}
		}
		if (ft_check_sem_pipe(str, i) && !check_quote)
			return (1);
	}
	return (0);
}

/**
 * handler_signal: a function to handle signal calls
 * @num: number of the signal status
*/
void	handler_signal(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \n", 4);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * validat_init_singal: validate and initialize the envionment
 * @ac: number of argument
 * @env: environment variables
 * @proc: my whole structure
*/
void	validat_init_singal(int ac, char **env, t_data *proc)
{
	if (ac > 1)
		exit(write(2, "Error: execute like <./minishell>\n", 35));
	g_err_code = 0;
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, SIG_IGN);
	if (env[0] == NULL)
		exit(printf("\033[1;31mError\033[0m: No env variable found:\n"));
	ft_linked_env(proc, env);
}

/**
 * validate_input: a simple validation,, check the input if its space and null
 * @proc: my whole structure
*/
int	validate_input(t_data *proc)
{
	if (!proc->main_line)
	{
		printf("exit\n");
		exit(g_err_code);
	}
	if (proc->main_line[0] == '\0')
		return (1);
	add_history(proc->main_line);
	if (ft_preparsing(proc->main_line))
	{
		printf("Error!!!\n");
		return (1);
	}
	return (0);
}

/**
 * main: where the main majic is happening,, take string ,validate, execute
 * @ac: number of arguments passed
 * @av: arguments passed
 * @env: the environment variable
*/
int	main(int ac, char **av, char **env)
{
	t_pipe	*pipe;
	t_data	proc;

	(void)av;
	validat_init_singal(ac, env, &proc);
	while (1)
	{
		// if (g_err_code == 0)
		// 	proc.main_line = readline \
		// 	("\001\033[32m\002" "minishell {🤣}-> " "\001\033[0m\002");
		// else
			proc.main_line = readline \
			("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		if (validate_input(&proc) == 1)
			continue ;
		proc.main_line = expand(proc.main_line);
		pipe = ft_lexer(proc.main_line, env);
		g_err_code = pipex(pipe->cmd_len, pipe, &proc);
	}
	return (0);
}
