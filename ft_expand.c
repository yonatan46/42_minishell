/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:10:20 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/02 16:36:21 by yonamog2         ###   ########.fr       */
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
			copy = ftt_strjoin(copy, ft_substr(str, start, x));
			// printf("come here: %s\n", copy);
		}
		if(str[x] == '$')
		{
			start = x;
			x++;
			while ((str[x]) && (str[x] != '$' && str[x] != ' '))
				x++;
			tmp = getenv(ft_substr(str, start + 1, x - 2));
			if (tmp == NULL)
				copy = ftt_strjoin(copy, "");
			else
				copy = ftt_strjoin(copy, ft_strdup(tmp));	
		}
		if (str[x] == '\0')
			break;
		// printf("car: %c\n", str[x]);
		x++;
	}
	printf("%s\n", copy);
	return(0);
}