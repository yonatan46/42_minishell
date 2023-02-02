/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:10:20 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/02 17:14:56 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*expand(char *str)
{
	char *copy;
	char *tmp;
	int x;
	int start;
	int flag_dq;
	int flag_sq;

	x = 0;
	start = 0;
	flag_dq = 0;
	flag_sq = 0;
	copy = NULL;
	tmp = NULL;
	while (str[x])
	{
		// if (str[x] == '\'')
		// 	flag_sq = !flag_sq;
		// else if (str[x] == '\"')
		// 	flag_dq = !flag_dq;
		// printf("dq: %d\n", flag_dq);
		// printf("s1: %d\n", flag_sq);
		// if (flag_dq == 1 || flag_sq == 1)
		// {
		// 	printf("sub: %s\n", ft_substr(str, x, 1));
		// 	copy = ftt_strjoin(copy, ft_substr(str, x, 1));
		// 	x++;
		// 	continue ;
		// }
		start = x;
		if (str[x] != '$')
		{
			while (str[x] && str[x] != '$')
				x++;
			copy = ftt_strjoin(copy, ft_substr(str, start, x));
		}
		if(str[x] == '$')
		{
			x++;
			start = x;
			while (str[x] != '$' && str[x] != ' ' && str[x])
				x++;
			tmp = getenv(ft_substr(str, start, x - start));
			if (tmp == NULL)
				copy = ftt_strjoin(copy, "");
			else
				copy = ftt_strjoin(copy, tmp);	
		}
		if (str[x] == '\0')
			break;
		x++;
	}
	printf("copy: %s\n", copy);
	return(free(str), copy);
}