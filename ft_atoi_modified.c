/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modified.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:42:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 21:02:10 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	atoi_utl_with_exit(char *str, int x, unsigned long long *res, \
unsigned long long *copy, t_data *proc, t_pipe *pipe)
{
	int	x;

	x = 0;
	while (str[x] >= '0' && str[x] <= '9')
	{
		*copy = *res;
		*res = (*res * 10) + (str[x++] - '0');
		if (*copy > *res)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			free_func(proc->envp);
			ultimate_free(proc, pipe);
			exit(255);
		}
	}
}

int	ft_atoi_ultra(const char *str, t_pipe *pipe, t_data *proc)
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
	atoi_utl_with_exit((char *)str, x, &res, &copy, proc, pipe);
	ft_util(res, sign);
	return (res * sign);
}
