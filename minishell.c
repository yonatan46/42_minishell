/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:02:12 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/12 21:32:49 by yonamog2         ###   ########.fr       */
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
		wait(0);
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
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("hello\n");
		g_err_code = 1;
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
	char **split;

	if(proc->main_line)
	{
		split = ft_split(proc->main_line, ' ');
		if (split[0] == NULL)
		{
			free_func(split);
			return (1);
		}
		free_func(split);
	}
	if (!proc->main_line)
	{
		printf("exit\n");
		free_list(*proc->head);
		free(proc->head);
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
	int		x;
	t_pipe	*pipe;
	t_data	proc;

	(void)av;
	validat_init_singal(ac, env, &proc);
	while (1)
	{
					proc.main_line = readline \
		("\001\033[32m\002" "minishell {😇}-> " "\001\033[0m\002");
		if (validate_input(&proc) == 1)
		{
			free(proc.main_line);
			g_err_code = 0;
			continue ;
		}
		pipe = ft_lexer(proc.main_line, &proc);
		if (pipe->cmd_len >= 200)
		{
			printf("duhh\n");
			exit(1);
		}
		if (check_and_update_heredoc(pipe, &proc) == 1)
		{
			x = 0;
			while (x < pipe->cmd_len)
			{
				free_func(pipe[x].f_cmd);
				x++;
			}
			free_redirection(pipe);
			if (pipe->arg)
				free_func(pipe->arg);
			if (pipe->cmd)
				free(pipe->cmd);
			if (pipe)
				free(pipe);
			continue ;
		}
		g_err_code = pipex(pipe->cmd_len, pipe, &proc);
		x = 0;
		while (x < pipe->cmd_len)
		{
			if (pipe[x].arg)
				free_func(pipe[x].arg);
			if (pipe[x].cmd)
				free(pipe[x].cmd);
			free_func(pipe[x].f_cmd);
			x++;
		}
		free_redirection(pipe);
		if (pipe)
			free(pipe);
		unlink(".tmp");
	}
	return (0);
}
		/**
		 * // if (g_err_code == 0)
		// // else
		// 	proc.main_line = readline \
		// 	("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		*/