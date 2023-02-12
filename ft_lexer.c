/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:53:15 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/12 15:19:00 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_arg(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	ft_count_quotes(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == c)
			count++;
	return (count);
}

void	ft_delete_argquotes(t_pipe *f_struct, char *str, int *i, int *j)
{
	int		z;
	int		f;
	int		k;
	char	*ch;
	char	*ch1;
	char 	*tmp;

	z = -1;
	k = 0;
	tmp = NULL;
	while (str[++z])
	{
		if (str[z] == '\'')
		{
			f = z;
			ch = ft_del_quotes(str, &z, '\'');
			ch1 = ft_substr(str, k, f);
			tmp = f_struct[*i].arg[*j];
			f_struct[*i].arg[*j] = ft_strjoin(ch1, ch);
			free(ch);
			free(ch1);
		}
		else if (str[z] == '\"')
		{
			f = z;
			ch = ft_del_quotes(str, &z, '\"');
			ch1 = ft_substr(str, k, f);
			// f_struct[*i].arg[*j] = ft_strjoin(ch1, ch);
			tmp = f_struct[*i].arg[*j];
			f_struct[*i].arg[*j] = ft_strjoin(ch1, ch);
			free(ch);
			free(ch1);
		}
		if (str[z] == '\0')
			break ;
		if (tmp)
			free(tmp);
	}
	if (tmp)
		free(tmp);
}

void	ft_delete_arg_quotes(t_pipe *f_struct)
{
	int		i;
	int		j;

	i = -1;
	while (f_struct[++i].arg)
	{
		j = -1;
		while (f_struct[i].arg[++j])
			ft_delete_argquotes(f_struct, f_struct[i].arg[j], &i, &j);
	}
}

char	*ft_check_pipe_after_red(char *str)
{
	int		i;
	int		j;
	int		count;
	int		len;
	int		check_quote;
	char	*vars;

	check_quote = 0;
	i = -1;
	j = 0;
	count = ft_calc_redpipe(str, '|');
	len = ft_strlen(str);
	vars = (char *)malloc(sizeof(char) * (len - count + 1));
	while (str[++i])
	{
		ft_quote_zero_one(str[i], '|', &check_quote);
		if (str[i] == '|' && !(check_quote))
		{
			if (i >= 1 && str[i] == '|' && str[i - 1] == '>')
				vars[j++] = str[++i];
			else
			vars[j++] = str[i];
		}
		else
			vars[j++] = str[i];
	}
	vars[j] = '\0';
	return (vars);
}

void ft_print_cmd(t_pipe *f_struct)
{
	int i;
	int j;

	i = 0;
	while (f_struct[i].arg || f_struct[i].red)
	{
	printf("---------<Structure = %i>--------\n", i);
		printf("CMD = %s\n", f_struct[i].cmd);	
		j =	0;
		while (f_struct[i].arg && f_struct[i].arg[j])
		{
			printf("	ARG = %s\n", f_struct[i].arg[j]);
			j++;
		}
		j =	0;
		while (f_struct[i].red && f_struct[i].red[j])
		{
			printf("		SIGN = %s\n", f_struct[i].red[j]->red_sign);
			printf("		NAME = %s\n", f_struct[i].red[j]->red_name);
			j++;
		}
		i++;
	}
	printf("----------------------------------\n");
 }


t_pipe	*ft_lexer(char *str, t_data	*proc)
{
	(void)proc;
	int		i;
	int		x;
	char	**vars;
	int		pipes_num;
	t_pipe	*f_struct;

	i = 0;
	str = ft_check_pipe_after_red(str);
	str = ft_add_sp_redname(str);
	pipes_num = ft_calc(str, '|');
	vars = ft_clean_sp_struct(ft_separate_sp_pipe(str, '|'));
	f_struct = ft_calloc(sizeof(t_pipe), pipes_num + 2);
	while (vars[i])
	{
		f_struct[i].f_cmd = ft_separate_sp_pipe(vars[i], ' ');
		f_struct[i].cmd_len = pipes_num + 1;
		i++;
	}
	ft_count_struct(f_struct);
	i = 0;
	x = 0;
	while (i < f_struct->cmd_len)
	{
		f_struct[i].cmd = expand(f_struct[i].cmd, proc);
		// f_struct[i].cmd = expand_dollar_sign(f_struct[i].cmd);
		
		x = 0;
		while (f_struct[i].arg && f_struct[i].arg[x])
		{
			f_struct[i].arg[x] = expand(f_struct[i].arg[x], proc);
			// f_struct[i].arg[x] = expand_dollar_sign(f_struct[i].arg[x]);
			x++;
		}
		x = 0;
		while (x < f_struct[i].red_len)
		{
			f_struct[i].red[x]->red_sign = expand(f_struct[i].red[x]->red_sign, proc);
			// f_struct[i].red[x]->red_sign = expand_dollar_sign(f_struct[i].red[x]->red_sign);
			f_struct[i].red[x]->red_name = expand(f_struct[i].red[x]->red_name, proc);
			// f_struct[i].red[x]->red_name = expand_dollar_sign(f_struct[i].red[x]->red_name);
			x++;
		}
		i++;
	}
	ft_delete_all_qoutes(f_struct);
	free_func(vars);
	if (str)
		free(str);
	return (f_struct);
}
