/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaratae <dkaratae@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:12:59 by dkaratae          #+#    #+#             */
/*   Updated: 2023/01/27 15:22:52 by dkaratae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_red_after(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '<' && str[i+1] == '<' && str[i+2] != ' ') 
			|| (str[i] == '>' && str[i+1] == '>' && str[i+2] != ' '))
		{
			count++;
			i += 2;	
		}
		else if ((str[i] == '<' && str[i+1] != ' ' && str[i+1] != '<') 
			|| (str[i] == '>' && str[i+1] != ' ' && str[i+1] != '>'))
			count++;
		i++;
	}
	return (count);
}

char *ft_add_sp_red_after(char *str)
{
	int i;
	int j;
	int len;
	int len_add;
	
	i = 0;
	j = 0;
	len = ft_strlen(str);
	len_add = ft_count_red_after(str);
	char *new_str = (char*)malloc(sizeof(char) * (len + len_add + 1));
	while (i < len)
	{
		if ((str[i] == '<' && str[i+1] == '<' && str[i+2] != ' ')
			|| (str[i] == '>' && str[i+1] == '>' && str[i+2] != ' '))
		{
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] != '<' && str[i + 1] != '>' && str[i + 1] != ' ')
			{
				new_str[j++] = str[i++];
				new_str[j++] = ' ';
			}
			else
				new_str[j++] = str[i++];
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int ft_count_red_before(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if ((i != 0 && str[i] == '<' && str[i-1] != ' ') 
            || (i != 0 && str[i] == '>' && str[i-1] != ' '))
        {
          if ((str[i-1] != '<' && str[i-1] != '>'))
            count++;
          else
            i++;    
        }
        i++;
    }
    return (count);
}

char *ft_add_sp_red_before(char *str)
{
    int i;
    int j;
    int len;
    int len_add;
    
    i = 0;
    j = 0;
    len = ft_strlen(str);
    len_add = ft_count_red_before(str);
    char *new_str = (char*)malloc(sizeof(char) * (len + len_add + 1));
    while (i < len)
    {
        if ((i != 0 && str[i] == '<' && str[i-1] != ' ') 
            || (i != 0 && str[i] == '>' && str[i-1] != ' '))
        {
          if ((str[i-1] != '<' && str[i-1] != '>'))
          {
              new_str[j++] = ' ';
              new_str[j++] = str[i++];
          }
          else
              new_str[j++] = str[i++];
        }
        else
            new_str[j++] = str[i++];
    }
    new_str[j] = '\0';
    return (new_str);
}



