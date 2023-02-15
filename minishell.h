/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:02:17 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/15 18:05:04 by yonamog2         ###   ########.fr       */
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
	char				*main_line;
	char				pwd[1024];
	t_list				*t_lst;
	char				**res;
	char				*result;
	char				*copy;
	char				**res1;
	char				**path_split;
	char				*path;
	char				**res2;
	int					fd[256][2];
	int					tmp;
	int					id;
	int					flag_in;
	int					flag_out;
	int					id1;
	int					x;
	int					i;
	int					status;
	int					flag;
	int					counter;
	int					cmd_len;
	int					middle_cmd;
	int					ac;
	int					total_pipe;
	char				**copy_env;
	char				**tmp_2d;
	t_list				**head;
	int					pid1;
	int					pid2;
	int					check;
	int					err_no;
	int					tmp_file_fd;
	int					index;
	char				*pars;
	char				**envp;
	unsigned long long	*res_atoi;
	unsigned long long	*copy_atoi;
}	t_data;

typedef struct s_red
{
	char				*red_sign;
	char				*red_name;
}		t_red;

/**
 * @s_pipe: the struct containing infor of a single process execution
*/
typedef struct s_pipe
{
	int		cmd_len;
	int		red_len;
	int		arg_len;
	char	*cmd;
	char	**arg;
	t_red	**red;
	char	**f_cmd;
}		t_pipe;

typedef struct s_exp_var
{
	char		*cp;
	char		*tmp;
	char		*tmp_ex;
	int			x;
	int			y;
	int			start;
	int			flag_sq;
	int			flag_dq;
	int			flag_pwd;
	int			flag_shlvl;
	int			flag_oldpwd;
	int			flag;
	int			last_index;
	int			last_pos;
	t_list		*tmp_list;

}		t_exp_var;

typedef struct s_heredoc_var
{
	int		file1;
	char	*tmp;
	char	*tmp2;
	int		ret;
}	t_heredoc_var;

typedef struct s_pars_var
{
	int		z;
	int		f;
	int		k;
	int		i;
	int		j;
	char	*ch;
	char	*ch1;
	char	*tmp;
}	t_pars_var;

int		g_err_code;
void	free_func(char **args);
char	*ft_join_spltd(char *str);
void	cmd_not_found(t_pipe *av, t_data *proc, int counter);
int		search(char **envp);
int		pipex(int ac, t_pipe *av, t_data *proc);
int		ft_cd(t_pipe *pipe, t_data *proc);
int		atoi_md(const char *str, t_pipe *pipe, t_data *proc);
int		check_nns(char *str);
void	child_signal_handler(int num);
void	ultimate_free(t_data *data, t_pipe *pipe);
void	comb_free(t_pipe *pipe, t_data *proc);
int		expand_util(t_exp_var *var, char *str);
void	first_process_util(t_data *proc, t_pipe *av, char **envp);
void	last_process_util(t_data *proc, t_pipe *av, char **envp);
void	expand_structs(t_pipe *f_struct, t_data *proc);
void	set_flag(t_exp_var *var, char *str);
/**
 * redirectin functions
*/
void	red_first_proc(t_pipe *av, int *flag, t_data *proc);
void	red_one_cmd(t_pipe *av, t_data *proc);
void	red_middle(t_pipe *av, int *flag_out, int *flag_in, t_data *proc);
void	red_last_proc(t_pipe *av, int *flag, t_data *proc);
void	ft_echo(t_pipe *pipe, t_data *proc, char **envp);
void	ft_pwd(t_data *data, t_pipe *pipe, char **envp);
void	ft_exit(t_pipe *pipe, t_data *proc);
// void	ft_store_env(char **env, t_data *pipe);
int		ft_cd(t_pipe *pipe, t_data *proc);
void	ft_env_print_linked(t_data *proc, t_pipe *av);
void	ft_linked_env(t_data *proc, char **env);
int		ft_export_print_linked(t_pipe *pipe, t_data *proc);
void	sort_list(t_list *head);
int		ft_unset(t_pipe *pipe, t_data *proc);
char	**linked_to_array(t_list *head);
// void	free_func_one_cmd(char **args);
void	free_func_one_cmd(t_pipe *av, t_data *proc, char **envp);
int		remove_element(t_list **head, int index);
void	ft_create_export(t_data *proc, char **env);
int		chek_exp_a_rplc(t_list *head, char *replace);
char	*ft_getenv(t_list *head, char *str);
char	*expand(char *str, t_data *pipe);
int		compare_until_eq(char *str1, char *str2);
int		chek_exp_a_rplc_util(t_exp_var *var, char *replace);
int		chek_exp_a_rplc(t_list *head, char *replace);
int		ft_validate_exprot(char *str);
void	print_and_set_flag(t_pipe *pipe, t_data *proc);
void	init_vars(t_exp_var *var);
int		ft_linked_env_util_2(t_exp_var *var, t_list *head, \
t_data *proc, char **env);
void	free_one_exec(t_data *proc, t_pipe *pipe);
int		ft_linked_env_util(t_exp_var *var, \
t_list *head, t_data *proc, char **env);
void	check_and_set(t_exp_var *var, t_list *head, t_data *proc);
void	ft_linked_env(t_data *proc, char **env);
int		red_output(t_pipe *av, int x, t_data *proc);
int		red_infile(t_pipe *av, int x, t_data *proc);
int		red_append_mode(t_pipe *av, int x, t_data *proc);
void	get_env_and_replace(t_exp_var *var, char *str);
/**
 * PARSING PART
*/

/* ft_preparse */
int		ft_check_loop_space(char *str, int *i);
int		ft_check_count_red(char *str, int i, char c);
int		ft_check_red_pipe(char *str);
int		ft_check_count_red_one(char *str);
int		ft_preparsing(char *str);

/* ft_checker_qoutes */
int		ft_check_qoutes(char *str);
int		ft_check_quote(char *str, char c, int *i);
int		f_check_aft_red_zero(char *str);
int		ft_check_sem_pipe_two(char *str, int *i);
int		ft_check_sem_pipe(char *str, int i);

/* ft_copy_to_struct */
int		ft_calc_redpipe(char *str, char c);
int		ft_calc(char *str, char c);
char	*ft_strcopy(char *dest, char *src, size_t n);
char	*ft_copy_to_struct(char **vars, char *str, int *arr);
char	**ft_separate_sp_pipe(char *str, char c);

/* ft_lexer */
int		ft_count_arg(char **str);
int		ft_count_quotes(char *str, char c);
void	ft_delete_argquotes(t_pipe *f_struct, char *str, int i, int j);
void	ft_delete_arg_quotes(t_pipe *f_struct);
t_pipe	*ft_lexer(char *str, t_data	*proc);

/* ft_redirection_del */
void	ft_delete_all_qoutes(t_pipe *f_struct);
void	ft_delete_redname_quotes(t_pipe *f_struct);
void	ft_copy_redname(t_pipe *f_struct, char *str, int *i, int *j);
void	ft_delete_cmd_quotes_two(t_pipe *f_struct);
char	*ft_del_quotes_two(char *str, char c);

/* ft_redirection_one */
void	ft_check_pipe_space(char *str, int *i);
int		ft_count_red_after(char *str);
char	ft_quote_zero_one(char str, char ch, int *check_quote);
void	ft_copy_dred_new_string(char *str, char *new_str, int *i, int *j);
void	ft_copy_sred_new_string(char *str, char *new_str, int *i, int *j);

/* ft_redirection_two */
int		ft_check_equal_dred(char *str, int i, int check_quote);
char	*ft_add_sp_red_after(char *str);
int		ft_count_red_before(char *str);
void	ft_copy_sred_before(char *str, char *new_str, int *i, int *j);
char	*ft_add_sp_red_before(char *str);

/* ft_redirection_utils */
int		ft_isspace(char ch);
int		ft_check_red_not_three(char *str);
char	*ft_add_sp_redname(char *str);
int		ft_count_red(char **s1);
char	*ft_del_quotes(char *str, int *i, char c);

/* ft_separate_struct */
void	ft_copy_red_sign(t_pipe *f_struct, int i, int j, int r);
void	ft_copy_red_name(t_pipe *f_struct, int i, int j, int r);
void	ft_copy_to_arg(t_pipe *f_struct, int i, int j, int *g);
void	ft_copy_to_red_sign_name(t_pipe *f_struct, int i, int *j, int *r);
void	ft_count_struct(t_pipe *f_struct);

/* ft_separate_utils */
int		ft_count_red_pipe(char **str, int count_all, int count_red);
int		ft_allocate_memory_red_arg(t_pipe *f_struct, int *i);

/* ft_space */
char	*ft_copy_after_clean_sp(char *str, int *i, int *k, int check_quote);
char	*ft_c_sp(char *str);
int		ft_trim_space(char *str, char c);
char	**ft_c_sp_struct(char **str);

/* minishell */
int		main(int ac, char **av, char **env);

// void	ft_print_cmd(t_pipe *f_struct);

void	print_2d(char **str);
void	ft_delete_arg_quotes(t_pipe *f_struct);
// char	*ft_del_quotes(char *str, int *i, char c);
int		ft_count_quotes(char *str, char c);
char	*ft_dollar(char *str, int *i, char **env);
int		ft_check_isalnum(char c);
char	*ft_change_dollar(char *str, char **env);
char	*parsing_middle(t_data *proc, char **envp, char *s);
char	*parsing(t_data *proc, char **envp, char *s);
int		ft_check_builtin(char *cmd);
void	check_built_ins_and_exexute_one_cmd(t_data *proc, \
t_pipe *av, char **envp);
void	one_cmd_process(t_data *proc, t_pipe *av, char **envp);
void	close_pipes(t_data *proc);
int		pipex_one_cmd(t_pipe *av, t_data *proc, char **envp);
void	check_built_ins_and_exexute(t_data *proc, t_pipe *av, char **envp);
int		first_process(t_data *proc, t_pipe *av, char **envp);
void	middle_proc_execute(t_data *proc, t_pipe *av, char **envp, int counter);
void	middl_process(t_data *proc, t_pipe *av, char **envp, int counter);
int		last_process(t_data *proc, t_pipe *av, char **envp);
int		check_and_update_heredoc(t_pipe *av, t_data *proc);
char	*get_next_line(int fd);
void	handler_signal(int num);
void	re_index(t_list *head);
void	free_list(t_list *head);
void	free_redirection(t_pipe *pipe);
void	terminate(char *m, t_data *proc, t_pipe *pipe);
char	*expand_env_vars(const char *str);
char	*expand_dollar_sign(const char *input);

void	ft_delete_cmd_quotes_two(t_pipe *f_struct);
char	*ft_del_quotes_two(char *str, char c);
int		ft_calc_redpipe(char *str, char c);
char	*ft_check_pipe_after_red(char *str);
int		ft_strcmp(const char *s1, const char *s2);
#endif