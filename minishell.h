/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:18:52 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/27 16:15:33 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "./libft/libft.h"
# include <readline/readline.h>
// #include <readline/history.h>

typedef struct s_red
{
	char	*red_sign;
	char	*red_name;
}	t_red;

typedef struct s_data
{
	char	*cmd;
	char	**arg;
	char	**f_cmd;
	int		red_len;
	t_red	**red;
}	t_data;

/* ft_checker_qoutes */
int	ft_check_qoutes(char *str);
int	ft_check_sem_pipe(char *str, int i);
int	ft_check_quote(char *str, char qute, int *i);

/* ft_copy_to_struct */
int	ft_calc(char *str, char c);
char	*ft_strcopy(char *dest, char *src, size_t n);
char	*ft_copy_to_struct(char **vars, char *str, int *arr);
char	**ft_separate_sp_pipe(char *str, char c);

/* ft_lexer */
int ft_count_arg(char **str);
void ft_lexer(char *str);

/* ft_redirection_utils */
int ft_check_red_not_three(char *str);
char *ft_add_sp_redname(char *str);
int	ft_count_red(char **s1);


/* ft_redirection */
int ft_count_red_after(char *str);
char *ft_add_sp_red_after(char *str);
int ft_count_red_before(char *str);
char *ft_add_sp_red_before(char *str);

/* ft_separate_struct */
void ft_copy_red_sign(t_data *f_struct, int i, int j, int r);
void ft_copy_red_name(t_data *f_struct, int i, int j, int r);
void ft_count_struct(t_data *f_struct);

/* ft_shell_utils */
int	ft_isspace(char ch);

/* ft_space */
char *ft_clean_spaces(char *str);
int ft_trim_space(char *str, char c);
char **ft_clean_sp_struct(char **str);


/* minishell */
int		ft_preparsing(char *str);
int		main(int ac, char **av, char **env);



void	ft_print_cmd(t_data *f_struct);
#endif
