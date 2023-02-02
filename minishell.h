/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:53:01 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/02 13:12:48 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./ft_printf/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
typedef struct s_data
{
	char	pwd[1024];
	t_list	*tmp_list;
	char	**res;
	char	*result;
	char	*copy;
	char	**res1;
	char	**path_split;
	char	*path;
	char	**res2;
	int		fd[256][2];
	int		tmp;
	int		id;
	int		flag_in;
	int		flag_out;
	int		id1;
	int		x;
	int		status;
	int		flag;
	int		counter;
	int		cmd_len;
	int		middle_cmd;
	int		ac;
	int		total_pipe;
	int		general_error_code;
	char	**copy_env;
	char	**tmp_2d;
	t_list	**head;
	t_list	**head_export;
	int		pid1;
	int		pid2;
	int		check;
	int		err_no;
}	t_data;

typedef struct s_red
{
	char	*red_sign;
	char	*red_name;
}		t_red;

typedef struct s_pipe
{
	int		cmd_len;
	int		red_len;
	int		err_no;
	char	*cmd;
	char	**arg;
	t_red	**red;
	char	**f_cmd;
}		t_pipe;

void	free_func(char **args);
void	terminate(char *m);
void	cmd_not_found(t_pipe *av);
int		search(char **envp);
int		pipex(int ac, t_pipe *av, t_data *proc);

/**
 * redirectin functions
*/
void	red_first_proc(t_pipe *av, int *flag);
void	red_one_cmd(t_pipe *av);
void	red_middle(t_pipe *av, int *flag_out, int *flag_in);
void	red_last_proc(t_pipe *av, int *flag);
void	ft_echo(t_pipe *pipe);
void	ft_pwd(void);
void	ft_exit(t_pipe *pipe, t_data *proc);
// void	ft_store_env(char **env, t_data *pipe);
void	ft_export(char **strings);
int		ft_cd(t_pipe *pipe, t_data *proc);
void	ft_env(char **env);
void	ft_env_print_linked(t_data *proc);
void	ft_linked_env(t_data *proc, char **env);
int		ft_export_print_linked(t_pipe *pipe, t_data *proc);
void	sort_list(t_list *head);
int		ft_unset(t_pipe *pipe, t_data *proc);
int		search_env_linked(t_list *head);
char	**linked_to_array(t_list *head);
// void	free_func_one_cmd(char **args);
void	free_func_one_cmd(t_pipe *av);
void	remove_element(t_list **head, int index);
void	ft_create_export(t_data *proc, char **env);
void	check_export_and_replace(t_list *head, char *replace);
char	*ft_getenv(t_list *head, char *str);
int expand(char *str);


/**
 * PARSING PART
*/

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
t_pipe *ft_lexer(char *str);

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
void ft_copy_red_sign(t_pipe *f_struct, int i, int j, int r);
void ft_copy_red_name(t_pipe *f_struct, int i, int j, int r);
void ft_count_struct(t_pipe *f_struct);

/* ft_shell_utils */
int	ft_isspace(char ch);

/* ft_space */
char *ft_clean_spaces(char *str);
int ft_trim_space(char *str, char c);
char **ft_clean_sp_struct(char **str);


/* minishell */
int		ft_preparsing(char *str);
int		main(int ac, char **av, char **env);



void	ft_print_cmd(t_pipe *f_struct);
#endif