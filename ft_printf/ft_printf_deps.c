/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_deps.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:26:11 by yonamog2          #+#    #+#             */
/*   Updated: 2022/11/15 05:56:35 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

int	ft_printstr(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[++i])
		write(1, &str[i], 1);
	return (i);
}

int	ft_printchar(int c)
{	
	write(1, &c, 1);
	return (1);
}

int	ft_printnbr(int n)
{
	int		len;
	char	*num;

	len = 0;
	num = ft_itoa(n);
	len = ft_printstr(num);
	free(num);
	return (len);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}
