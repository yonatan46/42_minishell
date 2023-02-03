/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:10:20 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/03 16:36:12 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*expand(char *str, t_data *proc)
{
	char *copy;
	char *tmp;
	int x;
	int start;
	int flag_sq;

	x = 0;
	start = 0;
	flag_sq = 0;
	copy = NULL;
	tmp = NULL;
	while (str[x])
	{
		if (str[x] == '\'')
			flag_sq = !flag_sq;
		if (flag_sq == 1)
		{
			copy = ftt_strjoin(copy, ft_substr(str, x, 1));
			x++;
			continue ;
		}
		start = x;
		if (str[x] != '$')
		{
			copy = ftt_strjoin(copy, ft_substr(str, x, 1));
			x++;
		}
		else if (str[x] == '$')
		{
			x++;
			if (flag_sq == 0)
			{
				if (str[x] == '?')
				{
					copy = ftt_strjoin(copy, ft_itoa(proc->general_error_code));
					x++;
					continue ;
				}
				else if (str[x] == ' ' || str[x] == '\0' || str[x] == '\"')
				{
					if (str[x] == '\"' || str[x] == ' ')
					{
						copy = ftt_strjoin(copy, ft_substr(str, x - 1, 2));
						x++;
					}
					else
						copy = ftt_strjoin(copy, ft_substr(str, x - 1, 1));
					x++;
					continue ;
				}
				start = x;
				while (str[x] != '$' && str[x] != ' ' && str[x] && str[x] != '\"')
					x++;
				tmp = getenv(ft_substr(str, start, x - start));
				if (tmp == NULL)
					copy = ftt_strjoin(copy, "");
				else
					copy = ftt_strjoin(copy, tmp);	
			}
		}
		if (str[x] == '\0')
			break ;
	}
	return (free(str), copy);
}