/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:02:12 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/15 18:07:16 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * validat_init_singal: validate and initialize the envionment
 * @ac: number of argument
 * @env: environment variables
 * @proc: my whole structure
*/
void	validat_init_singal(int ac, char **env, t_data *proc)
{
	signal(SIGQUIT, SIG_IGN);
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
	{
		g_err_code = 258;
		return (ft_putstr_fd("Syntax error near unexpected token\n", 2), 1);
	}
	return (0);
}

/**
 * main_util: 
*/
int	main_util(t_data *proc, t_pipe *pipe)
{
	if (pipe->cmd_len >= 220)
	{
		ft_putstr_fd("Sorry too many command\n", 2);
		exit(1);
	}
	if (check_and_update_heredoc(pipe, proc) == 1)
	{
		free_redirection(pipe);
		ultimate_free(proc, pipe);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handler_signal);
	g_err_code = pipex(pipe->cmd_len, pipe, proc);
	free_redirection(pipe);
	ultimate_free(NULL, pipe);
	unlink(".tmp");
	return (0);
}

void	sig_start(void)
{
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, SIG_IGN);
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
		sig_start();
		if (g_err_code == 0)
			proc.main_line = readline \
				("\001\033[32m\002" "minishell {😇}-> " "\001\033[0m\002");
		else
			proc.main_line = readline \
					("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		if (validate_input(&proc) == 1)
		{
			simple_free(proc.main_line);
			g_err_code = 0;
			continue ;
		}
		pipe = ft_lexer(proc.main_line, &proc);
		if (main_util(&proc, pipe) == 1)
			continue ;
	}
	return (0);
}
