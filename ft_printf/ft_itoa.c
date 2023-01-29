/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 18:06:23 by yonamog2          #+#    #+#             */
/*   Updated: 2023/01/16 18:18:52 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_nb(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static char	*re(void)
{
	char	*st;

	st = malloc (sizeof(char) * 2);
	st[0] = 48;
	st[1] = '\0';
	return (st);
}

char	*ft_itoa(int nb)
{
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = size_nb(n);
	if (n == 0)
		return (re());
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i--] = '0' + (n % 10);
		n = n / 10;
	}
	return (str);
}

// int main()
// {
// 	ft_printf("%s", ft_itoa(123));
// 	return(0);
// }