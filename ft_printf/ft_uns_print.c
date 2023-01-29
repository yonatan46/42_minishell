/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uns_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:50:22 by yonamog2          #+#    #+#             */
/*   Updated: 2022/11/15 06:00:41 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = num_len(n);
	num = malloc(sizeof(char) * (len + 1));
	if (!num)
		return (0);
	num[len--] = '\0';
	while (n > 0)
	{
		num[len--] = (n % 10) + 48;
		n = n / 10;
	}
	return (num);
}

int	ft_uns_print(unsigned int n)
{
	int		len;
	char	*num;

	len = 0;
	if (n == 0)
		len += ft_printchar('0');
	else
	{
		num = ft_uitoa(n);
		len += ft_printstr(num);
		free(num);
	}
	return (len);
}
