/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:00:54 by yonamog2          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/05 14:37:58 by dkaratae         ###   ########.fr       */
=======
/*   Updated: 2023/02/05 12:45:47 by yonamog2         ###   ########.fr       */
>>>>>>> 13e1b799c82fd8601878275121dd598ee2bc5a74
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
<<<<<<< HEAD
		// if (g_general_error_code == 0)
			proc.main_line = readline \
			("\001\033[32m\002" "minishell {🤣}-> " "\001\033[0m\002");
		// else
			// proc.main_line = readline("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		if (validate_input(&proc) == 1)
			continue ;
		proc.main_line = expand(proc.main_line, &proc);
		pipe = ft_lexer(proc.main_line);
		g_general_error_code = pipex(pipe->cmd_len, pipe, &proc);
=======
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
>>>>>>> 13e1b799c82fd8601878275121dd598ee2bc5a74
	}
	return (0);
}
