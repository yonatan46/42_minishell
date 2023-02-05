/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_to_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:31:57 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/05 11:55:28 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_calc(char *str, char c)
{
	int		i;
	int		check_quote;
	int		count;
	char	ch;

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
	int		v[3];
	int		check_quote;
	int		count;
	char	**vars;
	char	ch;

	v[0] = 0;
	v[1] = 0;
	v[2] = -1;
	check_quote = 0;
	count = ft_calc(str, c);
	vars = (char **)malloc(sizeof(char *) * (count + 2));
	while (str[++v[2]])
	{
		ch = ft_quote_zero_one(str[v[2]], ch, &check_quote);
		if (str[v[2]] == c && !(check_quote))
		{
			vars[v[0]] = ft_copy_to_struct(vars, str, &(*v));
			v[0]++;
			v[1] = v[2] + 1;
		}
	}
	vars[v[0]] = ft_copy_to_struct(vars, str, &(*v));
	vars[++v[0]] = NULL;
	return (vars);
}
