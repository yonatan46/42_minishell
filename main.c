/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:19:15 by yonamog2          #+#    #+#             */
/*   Updated: 2023/01/23 15:37:15 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int arrary_len(char **array)
{
	int x;

	x = 0;
	while (array[x])
		x++;
	return(x);
}
void handler_signal	(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 4);
		int status;
		wait(&status);
		if (WIFSIGNALED(status))
			printf("was terminated by signal %d\n", WTERMSIG(status));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// signal(SIGINT, handler_signal);
	}
}

int look_for_m(char *str)
{
	int x;
	
	x = -1;
	while (str[++x])
		if (str[x] == 13)
			return (1);
	return (0);
}
int main(int ac, char **av, char **env)
{
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
	(void)av;
	(void)ac;
	(void)env;
	int x;
	int code = 0;
	int len;
	char *input;
	char **input_array;
	t_pipe	pipe[50];
	// t_red	redire1[10];
	while (1)
	{
		// signal(SIGINT, handler_signal);
		if (code == 0)
			input = readline("\001\033[32m\002" "minishell {🤣}-> " "\001\033[0m\002");
		else
			input = readline("\001\033[1m\033[31m\002" "minishell {😡}-> " "\001\033[0m\002");
		if (!input)
		{
			printf("exit\n");
			exit(code);
		}
		if (look_for_m(input) != 0)
		{
			printf(" : command not found\n");
			continue ;
		}
		add_history(input);
		// printf("input: %s\n", input);
		input_array = ft_split(input, '|');
		len = arrary_len(input_array);
		// pipe[0].cmd = "first";
		// pipe[0].cmd_len = len + 1;
		// pipe[0].red_len = 0;
		x = 0;
		while (input_array[x])
		{
			// printf("%s\n", input_array[x]);
			pipe[x].cmd = input_array[x];
			pipe[x].cmd_len = len;
			pipe[x].red_len = 0;
			// check_add_red(&pipe[x]);
			x++;
		}
		// printf("%s\n", pipe[0].cmd);
		// printf("%s\n", pipe[1].cmd);
		// printf("len: %d",pipe->cmd_len);
		// printf("first: %s",pipe->cmd);
		// exit(1);
		code = pipex(pipe->cmd_len, pipe, &proc);
		printf("Errno: %d\n", code);
		// x = 0;
		// while (x < len)
		// {
		// 	printf("%d :\t%s\n", x, pipe[x].cmd);
		// 	x++;
		// }
		free(input);
			// count++;
	}
	
	// pipe[0].cmd = "hello";
	// pipe[0].cmd_len = 2;
	// pipe[1].cmd_len = 2;
	// pipe[2].cmd_len = 2;
	// pipe[3].cmd_len = 2;
	// pipe[4].cmd_len = 2;
	// pipe[5].cmd_len = 2;
	// pipe[0].red_len = 0;
	// pipe[1].red_len = 1;
	// pipe[2].red_len = 0;
	// pipe[3].red_len = 0;
	// pipe[4].red_len = 0;
	// pipe[5].red_len = 0;
	// pipe[1].cmd = "ls";
	// // pipe[1].arg[0] = "-n";
	// // pipe[1].arg[1] = "what ever text you have";
	// // pipe[1].arg[2] = NULL;
	// pipe[2].cmd = "ls";
	// pipe[3].cmd = "grep main";
	// pipe[4].cmd = "cat";
	// pipe[5].cmd = "cat";
	// redire1[0].red = ">>";
	// redire1[0].file_name = "hello";
	// redire1[1].red = ">";
	// redire1[1].file_name = "yoni";
	// pipe[1].red = redire1;
	
	// printf("first |%s|\n", pipe[1].cmd);
	// printf("first_redirection_red|%s|\n", pipe[1].red[0].red);
	// printf("first_redirection_filename|%s|\n", pipe[1].red[0].file_name);
	// printf("--------------------------------------------------------\n");
	// printf("first_redirection_red|%s|\n", pipe[1].red[1].red);
	// printf("first_redirection_filename|%s|\n", pipe[1].red[1].file_name);
	// printf("first_redirection_red|%s|\n", pipe[1].red[0].red);
	// printf("first_redirection_filename|%s|\n", pipe[1].red[0].file_name);
	// printf("second|%s|\n", pipe[2].cmd);
	// printf("second_redirection_red|%s|\n", pipe[2].red->red);
	// printf("second_redirection_filename|%s|\n", pipe[2].red->file_name);
	// t_red	redire2[10];

	// printf("redirection_file_name |%s|\n", pipe[2].red->red);
	// printf("redirection_file_name |%s|\n", pipe[2].red->file_name);
	// printf("redirection_file_name |%s|\n", pipe[1].red->red);
	// printf("redirection_file_name |%s|\n", pipe[1].red->file_name);
	// printf("cmd2 |%s|\n", pipe[1].cmd);
	// printf("cmd3 |%s|\n", pipe[2].cmd);
	// pipe->cmd_len = 3;
	// pipe->red_len = 1;
	// char *ap[3];
	// ap[0] = "cat";
	// ap[1] = "-la";
	// ap[2] = NULL;
	// execve("/bin/ls", ap, NULL);
	// pipex(pipe->cmd_len, pipe, env);
	// printf("access: |%d|\n", access("..///////", 0));
	// char *a[] = {"/bin/echo", "hello world" ,"plus other string", NULL};
	// if(execve(a[0], a, NULL) == -1)
	// 	printf("Failed\n");
	// input_prompt();
	// int file1 = open("new", O_RDWR | O_CREAT | O_APPEND, 0777);
	// close(file1);
	return(0);
}
