/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:52:10 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/06 17:44:37 by yonamog2         ###   ########.fr       */
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
void	ft_echo(t_pipe *pipe)
{
	int	x;

	x = 0;
	if (pipe->arg[1] == NULL)
		printf("\n");
	else if (strcmp(pipe->arg[1], "-n") == 0)
	{
		x++;
		ft_print_echo(pipe, x);
	}
	else
	{
		ft_print_echo(pipe, x);
		printf("\n");
	}
	exit(0);
}

/**
 * ft_pwd: will print the current directory
*/
void	ft_pwd(t_data *data, t_pipe *pipe, char **envp)
{
	(void)pipe;
	(void)data;
	char	res[1024];
	char	*pwd;

	pwd = getcwd(res, 1024);
	if (!pwd)
	{
		ft_putstr_fd("Error: sorry dir is deleted or incorrect!\n", 2);
		// free_func(pipe->arg);
		// free_func(envp);
		// free(pipe->cmd);
		exit(1);
	}
	printf("%s\n", pwd);
	free_list(*data->head);
	free_func(envp);
	free_func(pipe->arg);
	free(pipe->cmd);
	close(0);
	close(1);
	close(2);
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
void	ft_exit(t_pipe *pipe)
{
	int		err_code;

	err_code = 0;
	if (pipe->arg[1] == NULL)
		exit(g_err_code);
	if (pipe->arg[2])
	{
		write(2, pipe->cmd, ft_strlen(pipe->cmd));
		ft_putstr_fd(": too many arguments\n", 2);
		return ;
	}
	if (scan_exit_codes(pipe) == 1)
	{
		write(2, pipe->cmd, ft_strlen(pipe->cmd));
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (pipe->arg[1])
		err_code = (unsigned char)ft_atoi(pipe->arg[1]);
	exit(err_code);
}
