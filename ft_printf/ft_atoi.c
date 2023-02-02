/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:46:38 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/02 08:56:08 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				x;
	int				sign;
	unsigned long	res;
	unsigned long	copy;

	x = 0;
	res = 0;
	sign = 1;
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
	while (str[x] >= '0' && str[x] <= '9')
	{
		copy = res;
		res = (res * 10) + (str[x++] - '0');
		if (copy > res)
		{
			write(2, ": numeric argument required\n", 29);
			exit(255);
		}
	}
	return (res * sign);
}
