/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:12:59 by dkaratae          #+#    #+#             */
/*   Updated: 2023/02/02 17:33:33 by yonamog2         ###   ########.fr       */
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
	int check_quote;
	char ch;
	
	i = 0;
	j = 0;
	check_quote = 0;
	len = ft_strlen(str);
	len_add = ft_count_red_after(str);
	char *new_str = (char*)malloc(sizeof(char) * (len + len_add + 1));
	while (i < len)
	{
		if (!check_quote || ch == str[i])
		{
			if (str[i] == '\"' || str[i] == '\'')
			{
				check_quote = !check_quote;
				ch = str[i];
			}
		}
		if ((!check_quote && (str[i] == '<' && str[i+1] == '<' && str[i+2] != ' '))
			|| (!check_quote && (str[i] == '>' && str[i+1] == '>' && str[i+2] != ' ')))
		{
			new_str[j++] = str[i++];
			new_str[j++] = str[i++];
			new_str[j++] = ' ';
		}
		else if (!check_quote && (str[i] == '<' || str[i] == '>'))
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
	int check_quote;
	char ch;
    
    i = 0;
    j = 0;
	check_quote = 0;
    len = ft_strlen(str);
    len_add = ft_count_red_before(str);
    char *new_str = (char*)malloc(sizeof(char) * (len + len_add + 1));
    while (i < len)
    {
		if (!check_quote || ch == str[i])
		{
			if (str[i] == '\"' || str[i] == '\'')
			{
				check_quote = !check_quote;
				ch = str[i];
			}
		}
        if ((!check_quote && (i != 0 && str[i] == '<' && str[i-1] != ' ')) 
            || (!check_quote && (i != 0 && str[i] == '>' && str[i-1] != ' ')))
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



