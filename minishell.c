/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:53:06 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/04 15:53:08 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_loop_space(char *str, int *i)
{
	int count;
	// char sign;

	count = 0;
	// sign = str[*i];
	while (ft_isspace(str[++(*i)]))
		count++;
	if (count == 0)
		return (1);
	return (0);
}

int ft_check_red_pipe(char *str)
{
	int i;

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
	int	i;
	int	check_quote;
	char ch;

	check_quote = 0;
	i = 0;
	while ((ft_isspace(str[i])))
		i++;
	// if (ft_check_red_not_three(str))
	// 	return (1);
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
void handler_signal	(int num)
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
int	main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		write(2, "Error: execute like <./minishell>\n", 35);
		exit(42);
	}
	// char	**vars;
	char	*str;
	t_pipe *pipe;
	// char	*str1;
	t_data	proc;
	int code = 0;
	proc.general_error_code = 0;
	
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
		// if (code == 0)
			str = readline("\001\033[32m\002" "minishell {🤣}-> " "\001\033[0m\002");
		// else
		// 	str = readline("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		if (!str)
		{
			printf("exit\n");
			exit(code);
		}
		if (str[0] == '\0')
			continue ;
		add_history(str);
		if (ft_preparsing(str))
		{
			printf("Error!!!\n");
			continue ;
		}
		str = expand(str, &proc);
		pipe = ft_lexer(str, env);
		code = pipex(pipe->cmd_len, pipe, &proc);
		proc.general_error_code = code; 
		// ft_print_cmd(pipe);
	}
	return (0);
}

	// string: echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
    // output: {echo, "hello      there", how, are, 'you 'doing?, pixel, |, wc, -l, >, outfile, NULL}
	// echo "hello world | " | ls cat pwd "|" | export asdkasjdb '|'
	// echo "hello world | " | ls cat pwd "|" | export asdkasjdb '|' | echo <<abc|ls >>abc|cmd <abc -la|>abc 
	// printf("res: %s", getenv(""))