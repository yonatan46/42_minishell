/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:52:10 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/09 21:43:29 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_print_echo: print arguments to the terminal
 * @pipe: the structure containint the commands, redirections and args
 * @x: the indexing for the ags
*/
void	ft_print_echo(t_pipe *pipe, int x)
{
	while (pipe->arg[++x])
	{
		if (pipe->arg[x + 1] == NULL)
			printf("%s", pipe->arg[x]);
		else
			printf("%s ", pipe->arg[x]);
	}
}

/**
 * ft_echo: will just take a string and print it
 * @pipe: a structure that hold the whole commands and args
*/
void	ft_echo(t_pipe *pipe, t_data *proc, char **envp)
{
	(void)envp;
	int	x;

	x = 0;
	if (pipe->arg[1] == NULL || pipe->arg[1][0] == '\0')
	{
		printf("\n");
		free_func(envp);
		int x = 0;
		while (x < pipe->cmd_len)
		{
			free_func(pipe[x].f_cmd);
			x++;
		}
		free_redirection(pipe);
		free_list(*proc->head);
		free(proc->head);
		free_func(pipe->arg);
		free(pipe->cmd);
		free(pipe);
	}
	else if (strcmp(pipe->arg[1], "-n") == 0)
	{
		x = 1;
		ft_print_echo(pipe, x);
		free_func(envp);
		x = 0;
		while (x < pipe->cmd_len)
		{
			free_func(pipe[x].f_cmd);
			x++;
		}
		free_redirection(pipe);
		free_list(*proc->head);
		free(proc->head);
		free_func(pipe->arg);
		free(pipe->cmd);
		free(pipe);
	}
	else
	{
		x = 0;
		ft_print_echo(pipe, x);
		printf("\n");
		int x = 0;
		while (x < pipe->cmd_len)
		{
			free_func(pipe[x].f_cmd);
			x++;
		}
		free_redirection(pipe);
		free_func(envp);
		free_list(*proc->head);
		free(proc->head);
		// printf("here\n");
		free_func(pipe->arg);
		free(pipe->cmd);
		free(pipe);
	}
	exit(0);
}

void	free_redirection(t_pipe *pipe)
{
	int	x;
	int	i;

	x = 0;
	while (x < pipe->cmd_len)
	{
		i = 0;
		while (i < pipe[x].red_len)
		{
			free(pipe[x].red[i]->red_name);
			free(pipe[x].red[i]->red_sign);
			free(pipe[x].red[i]);
			i++;
		}
		free(pipe[x].red);
		x++;
	}
}
/**
 * ft_pwd: will print the current directory
*/
void	ft_pwd(t_data *data, t_pipe *pipe, char **envp)
{
	(void)pipe;
	(void)data;
	(void)envp;
	char	res[1024];
	char	*pwd;
	int x = 0;


	pwd = getcwd(res, 1024);
	if (!pwd)
	{
		ft_putstr_fd("Error: sorry dir is deleted or incorrect!\n", 2);
		// free_func(pipe->arg);
		// free_func(envp);
		// free(pipe->cmd);
		free_func(envp);
		exit(1);
	}
	printf("%s\n", pwd);
	free_list(*data->head);
	free(data->head);
	free_func(envp);
	free_redirection(pipe);
	while (x < pipe->cmd_len)
	{
		free(pipe[x].cmd);
		free_func(pipe[x].arg);
		free_func(pipe[x].f_cmd);
		x++;
	}
	free(pipe);
	exit(0);
}

/**
 * scan_exit_codes: just scan the sargs of exit,
 * @pipe: the structure containin the whole command, args and redirections
*/
int	scan_exit_codes(t_pipe *pipe)
{
	int	j;

	j = -1;
	while (pipe->arg[1][++j])
	{
		if (j == 0 && (pipe->arg[1][j] == '+' || pipe->arg[1][j] == '-'))
			continue ;
		if (ft_isdigit(pipe->arg[1][j]) == 0)
			return (1);
	}
	return (0);
}

/**
 * ft_exit: will print the current directory
 * @pipe: the struct that contains the whold command and instructions
*/
void	ft_exit(t_pipe *pipe, t_data *proc)
{
	int		err_code;

	err_code = 0;
	if (pipe[proc->index].arg[1] == NULL)
	{
		free_list(*proc->head);
		free(proc->head);
		free_func(proc->envp);
		free_redirection(pipe);
		int x = 0;
		while (x < pipe->cmd_len)
		{
			free(pipe[x].cmd);
			free_func(pipe[x].arg);
			free_func(pipe[x].f_cmd);
			x++;
		}
		free(pipe);
		exit(g_err_code);
	}
	if (pipe[proc->index].arg[2])
	{
		write(2, pipe[proc->index].cmd, ft_strlen(pipe[proc->index].cmd));
		ft_putstr_fd(": too many arguments\n", 2);
		return ;
	}
	if (scan_exit_codes(&pipe[proc->index]) == 1)
	{
		write(2, pipe[proc->index].cmd, ft_strlen(pipe[proc->index].cmd));
		ft_putstr_fd(": numeric argument required\n", 2);
		free_list(*proc->head);
		free(proc->head);
		free_func(proc->envp);
		free_redirection(pipe);
		int x = 0;
		while (x < pipe->cmd_len)
		{
			free(pipe[x].cmd);
			free_func(pipe[x].arg);
			free_func(pipe[x].f_cmd);
			x++;
		}
		free(pipe);
		exit(255);
	}
	if (pipe[proc->index].arg[1])
		err_code = (unsigned char)ft_atoi_ultra(pipe[proc->index].arg[1], pipe, proc);
	free_list(*proc->head);
	free(proc->head);
 	free_func(proc->envp);
	free_redirection(pipe);
	int x = 0;
	while (x < pipe->cmd_len)
	{
		free(pipe[x].cmd);
		free_func(pipe[x].arg);
		free_func(pipe[x].f_cmd);
		x++;
	}
	free(pipe);
	exit(err_code);
}
