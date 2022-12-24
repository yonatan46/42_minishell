/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:06:32 by yonamog2          #+#    #+#             */
/*   Updated: 2022/12/24 13:33:26 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data
{
	char	**res;
	char	*result;
	char	**res1;
	int		fd[2];
	int		id;
	int		id1;
	int		x;
	int		file1;
	int		file2;
}	t_data;


int		ft_isprint(int c);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *s1);
int		ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif