/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:31:57 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/02 13:21:05 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_calc(char *str, char c)
{
	int	i;
	int	check_quote;
	int	count;
	char ch;

	i = -1;
	check_quote = 0;
	count = 0;
	while (str[++i])
	{
		if (!check_quote || ch == str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				ch = str[i];
				check_quote = !check_quote;
			}
		}
		// if (str[i] == '\'' || str[i] == '\"')
		// 	check_quote = !check_quote;
		if (str[i] == c && !check_quote)
			count++;
	}
	return (count);
}

char	*ft_strcopy(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char	*ft_copy_to_struct(char **vars, char *str, int *arr)
{
	vars[arr[0]] = (char *)malloc(arr[2] - arr[1] + 1);
	return (ft_strcopy(vars[arr[0]], str + arr[1], arr[2] - arr[1]));
}

char	**ft_separate_sp_pipe(char *str, char c)
{
	int	arr[3];
	int	check_quote;
	int	count;
	char **vars;
	char ch;

	arr[0] = 0;
	arr[1] = 0;
	arr[2] = -1;
	check_quote = 0;
	count = ft_calc(str, c);
	vars = (char **)malloc(sizeof(char *) * (count + 2));
	while (str[++arr[2]])
	{
		if (!check_quote || ch == str[arr[2]])
		{
			if (str[arr[2]] == '\'' || str[arr[2]] == '\"')
			{
				ch = str[arr[2]];
				check_quote = !check_quote;
			}
		}
		if (str[arr[2]] == c && !(check_quote))
		{
			vars[arr[0]] = ft_copy_to_struct(vars, str, &(*arr));
			arr[0]++;
			arr[1] = arr[2] + 1;
		}
	}
	vars[arr[0]] = ft_copy_to_struct(vars, str, &(*arr));
	vars[++arr[0]] = NULL;
	return (vars);
}