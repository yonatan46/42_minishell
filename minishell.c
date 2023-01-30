/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:06:41 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/30 14:00:01 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int code = 0;
int	ft_preparsing(char *str)
{
	int	i;

	i = 0;
	while ((ft_isspace(str[i])))
		i++;
	if (ft_check_red_not_three(str))
		return (1);
	if (str[i] == '|' || str[i] == ';')
		return (1);
	if (ft_check_qoutes(str))
		return (1);
	i = -1;
	while (str[++i])
		if (ft_check_sem_pipe(str, i))
			return (1);
	return (0);
}
void handler_signal	(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 4);
		// int status;
		// wait(&status);
		// if (WIFSIGNALED(status))
		// 	printf("was terminated by signal %d\n", WTERMSIG(status));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// signal(SIGINT, handler_signal);
	}
}
int	main(int ac, char **av, char **env)
{
	// char	**vars;
	char	*str;
	t_pipe *pipe;
	// char	*str1;
	t_data	proc;

	signal(SIGINT, handler_signal);
	signal(SIGQUIT, SIG_IGN);
	// ft_linked_env(&proc, env, 1);
	if (env[0] == NULL)
	{
		printf("\033[1;31mError\033[0m: No env variable found:\n");
		exit(1);
	}
	ft_linked_env(&proc, env);
	(void)ac;
	(void)av;
	(void)env;
	(void)pipe;
	while (1)
	{
		if (code == 0)
			str = readline("\001\033[32m\002" "minishell {😁}-> " "\001\033[0m\002");
		else
			str = readline("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		if (!str)
		{
			printf("exit\n");
			exit(code);
		}
		add_history(str);
		if (ft_preparsing(str))
		{
			printf("Error\n");
			continue ;
		}
		pipe = ft_lexer(str);
		// ft_print_cmd(pipe);
		code = pipex(pipe->cmd_len, pipe, &proc);
		printf("Errno: %d\n", code);
	}
	return (0);
}

	// string: echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
    // output: {echo, "hello      there", how, are, 'you 'doing?, pixel, |, wc, -l, >, outfile, NULL}
	// echo "hello world | " | ls cat pwd "|" | export asdkasjdb '|'
	// echo "hello world | " | ls cat pwd "|" | export asdkasjdb '|' | echo <<abc|ls >>abc|cmd <abc -la|>abc 
	// printf("res: %s", getenv(""))