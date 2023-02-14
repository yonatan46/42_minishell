/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:46:38 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/14 12:53:34 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_util(unsigned long long res, int sign)
{
	if (sign == -1)
	{
		if ((res - 1) > LLONG_MAX)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	else
	{
		if (res > LLONG_MAX)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
}

void	atoi_utl_2(char *str, int x, unsigned long long *res, \
unsigned long long *copy)
{
	while (str[x] >= '0' && str[x] <= '9')
	{
		*copy = *res;
		*res = (*res * 10) + (str[x++] - '0');
		if (*copy > *res)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
}

int	ft_atoi(const char *str)
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
	atoi_utl_2((char *)str, x, &res, &copy);
	ft_util(res, sign);
	return (res * sign);
}
