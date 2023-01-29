/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:26:19 by yonamog2          #+#    #+#             */
/*   Updated: 2023/01/06 22:03:39 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formats(va_list arg, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_printchar(va_arg(arg, int));
	else if (format == 's')
		len += ft_printstr(va_arg(arg, char *));
	else if (format == 'd' || format == 'i')
		len += ft_printnbr(va_arg(arg, int));
	else if (format == 'u')
		len += ft_uns_print(va_arg(arg, unsigned int));
	else if (format == 'p')
		len += ft_ptr_print(va_arg(arg, unsigned long long));
	else if (format == 'x' || format == 'X')
		len += ft_hex_print(va_arg(arg, unsigned int), format);
	else if (format == '%')
		len += ft_printpercent();
	return (len);
}

int	ft_printf(char *str, ...)
{
	va_list	arg;
	int		x;
	int		len;

	x = -1;
	len = 0;
	va_start(arg, str);
	while (str[++x] != '\0')
	{
		if (str[x] == '%')
			len += ft_formats(arg, str[++x]);
		else
			len += ft_printchar(str[x]);
	}
	va_end(arg);
	return (len);
}
