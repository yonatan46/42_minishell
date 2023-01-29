/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:46:38 by yonamog2          #+#    #+#             */
/*   Updated: 2022/09/23 09:46:19 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					x;
	int					sign;
	unsigned long long	res;

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
		res = (res * 10) + (str[x++] - '0');
	if (res >= LONG_MAX && sign == 1)
		return (-1);
	if (res >= LONG_MAX && sign == -1)
		return (0);
	return (res * sign);
}
