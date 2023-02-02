/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:10:20 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/02 14:43:46 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand(char *str)
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
		// if (str[x] == '\'')
		// 	flag_sq = !flag_sq;
		// if (flag_dq == 1 || flag_sq == 1)
		// {
		// 	x++;
		// 	continue ;
		// }
		start = x;
		if (str[x] != '$')
		{
			while (str[x] && str[x] != '$')
				x++;
			copy = ft_strjoin(copy, ft_substr(str, start, x));	
		}
		// if(str[x] == '$')
		// {
		// 	start = x;
		// 	x++;
		// 	while ((str[x]) && (str[x] != '$' && str[x] != ' '))
		// 		x++;
		// 	tmp = getenv(ft_substr(str, start + 1, x - 2));
		// 	if (tmp == NULL)
		// 		copy = ft_strjoin(copy, "");
		// 	else
		// 		copy = ft_strjoin(copy, tmp);	
		// }
		if (str[x] == '\0')
			break;
		x++;
	}
	printf("%s\n", copy);
	return(0);
}