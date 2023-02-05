/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:15:36 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/05 15:56:11 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_red_not_three(char *str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{
		count = 0;
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] == '<' || str[i] == '>' || str[i] == ' ')
			{
				if (str[i] != ' ')
					count++;
				i++;
			}
			if (count > 2)
				return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_add_sp_redname(char *str)
{
	char	*new_str;

	new_str = ft_clean_spaces(str);
	new_str = ft_add_sp_red_after(new_str);
	new_str = ft_add_sp_red_before(new_str);
	return (new_str);
}

int	ft_count_red(char **s1)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s1[i])
	{
		if (s1[i][0] == '<' && s1[i][1] == '\0')
			count++;
		else if (s1[i][0] == '>' && s1[i][1] == '\0')
			count++;
		else if (s1[i][0] == '<' && s1[i][1] == '<' && s1[i][2] == '\0')
			count++;
		else if (s1[i][0] == '>' && s1[i][1] == '>' && s1[i][2] == '\0')
			count++;
		i++;
	}
	return (count);
}
