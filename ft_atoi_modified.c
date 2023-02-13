/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modified.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:42:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 22:35:14 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	atoi_utl_with_exit(char *str, int x, t_data *proc, t_pipe *pipe)
{
	while (str[x] >= '0' && str[x] <= '9')
	{
		*proc->copy_atoi = *proc->res_atoi;
		*proc->res_atoi = (*proc->res_atoi * 10) + (str[x++] - '0');
		if (*proc->copy_atoi > *proc->res_atoi)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			free_func(proc->envp);
			ultimate_free(proc, pipe);
			exit(255);
		}
	}
}

int	atoi_md(const char *str, t_pipe *pipe, t_data *proc)
{
	int						x;
	int						sign;
	unsigned long long		res;
	unsigned long long		copy;

	x = 0;
	res = 0;
	sign = 1;
	copy = 0;
	while (str[x] == ' ' || str[x] == '\n'
		|| str[x] == '\t'
		|| str[x] == '\v' || str[x] == '\r'
		|| str[x] == '\f')
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			sign = -1;
		x++;
	}
	proc->res_atoi = &res;
	proc->copy_atoi = &copy;
	atoi_utl_with_exit((char *)str, x, proc, pipe);
	ft_util(res, sign);
	return (res * sign);
}
