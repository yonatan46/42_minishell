/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:02:12 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/14 11:39:23 by yonamog2         ###   ########.fr       */
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
		ft_putstr_fd("  \n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_err_code = 1;
	}
}

void	child_signal_handler(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		g_err_code = 130;
	}
	else if (num == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		g_err_code = 130;
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
	char	**split;

	if (proc->main_line)
	{
		split = ft_split(proc->main_line, ' ');
		if (split[0] == NULL)
			return (free_func(split), 1);
		free_func(split);
	}
	if (!proc->main_line)
	{
		printf("exit\n");
		free_list(*proc->head);
		simple_free(proc->head);
		exit(g_err_code);
	}
	if (proc->main_line[0] == '\0')
		return (1);
	add_history(proc->main_line);
	if (ft_preparsing(proc->main_line))
		return (ft_putstr_fd("Syntax error near unexpected token\n", 2), 1);
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
	int		x;
	t_pipe	*pipe;
	t_data	proc;

	(void)av;
	validat_init_singal(ac, env, &proc);
	while (1)
	{
		signal(SIGINT, handler_signal);
		// if (g_err_code == 0)
			proc.main_line = readline \
				("\001\033[32m\002" "minishell {😇}-> " "\001\033[0m\002");
				/**
				 * to be changed!!!!!!!!!!
				*/
				proc.main_line = expand(proc.main_line, &proc);
		// else
		// 	proc.main_line = readline \
		// 			("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		if (validate_input(&proc) == 1)
		{
			simple_free(proc.main_line);
			g_err_code = 0;
			continue ;
		}
		pipe = ft_lexer(proc.main_line, &proc);
		if (pipe->cmd_len >= 220)
		{
			ft_putstr_fd("Sorry too many command\n", 2);
			exit(1);
		}
		if (check_and_update_heredoc(pipe, &proc) == 1)
		{
			x = 0;
			free_redirection(pipe);
			ultimate_free(&proc, pipe);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, handler_signal);
		g_err_code = pipex(pipe->cmd_len, pipe, &proc);
		x = 0;
		free_redirection(pipe);
		ultimate_free(NULL, pipe);
		unlink(".tmp");
	}
	return (0);
}
