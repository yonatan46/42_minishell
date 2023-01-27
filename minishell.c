/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:06:41 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/27 16:09:11 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int ac, char **av, char **env)
{
	// char	**vars;
	char	*str;
	// char	*str1;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		str = readline("minishell:> ");
		add_history(str);
		if (ft_preparsing(str))
		{
			printf("Error\n");
			continue ;
		}
		ft_lexer(str);
	}
	return (0);
}

	// string: echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
    // output: {echo, "hello      there", how, are, 'you 'doing?, pixel, |, wc, -l, >, outfile, NULL}
	// echo "hello world | " | ls cat pwd "|" | export asdkasjdb '|'
	// echo "hello world | " | ls cat pwd "|" | export asdkasjdb '|' | echo <<abc|ls >>abc|cmd <abc -la|>abc 
	// printf("res: %s", getenv(""))