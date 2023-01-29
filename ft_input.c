/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:01:00 by yonamog2          #+#    #+#             */
/*   Updated: 2023/01/09 18:33:22 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static	int validate_s_d_quote(char *str)
{
	int x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '\'')
		{
			x++;
			while (str[x] != '\'' && str[x] != '\0')
				x++;
			if (str[x] == '\0')
			{
				printf("Error: parse error near \'\n");
				return (1);
			}
		}
		if (str[x] == '\"')
		{
			x++;
			while (str[x] != '\"' && str[x] != '\0')
				x++;
			if (str[x] == '\0')
			{
				printf("Error: parse error near \"\n");
				return (1);
			}
		}
		x++;
	}
	printf("valid input\n");
	return(0);
}
int pipe_number(char *str)
{
	int x;
	int counter;
	int flag;

	counter = 0;
	x = -1;
    flag = 0;
	while (str[++x])
	{
        if (str[x] == '\'' || str[x] == '\"')
            flag = !flag;
		if (flag == 0)
        {
            if(str[x] == '|')
            {
                str[x] = 12;
                counter++;
            }
        }
	}
	printf("there are |%d| cmds\n", counter + 1);
	return(counter);
}
void init_pipe(t_pipe *pipe, int cmd_count, char *input)
{
	(void)pipe;
	(void)cmd_count;
	char **splited;
	int x;
	int x_cp;
	int flag;

	x = 0;
	x_cp = 0;
    flag = 0;
	splited = ft_split(input, 12);
	// while (splited[++x])
	// {
        int y = 0;
		// printf("%d, command = |%s|\n", x, splited[x]);
        while (splited[x][y])
        {
            // printf("found red: %s\n",&splited[x][y]);                   
            if (splited[x][y] == '\'' || splited[x][y] == '\"')
                flag = !flag;
            if (flag == 0)
            {
                if (splited[x][y] == '>' || splited[x][y] == '<' )
                {
                    printf("C: %c\n",splited[x][y]);
                    y++;
                    while(splited[x][y] == ' ')
                        y++;
                    x_cp = y;
                    while (splited[x][y] != ' ' && splited[x][y])
                        y++;
                    while (x_cp < y)
                    {
                        printf("C: %c\n",splited[x][x_cp]);                   
                        x_cp++;
                    }
                }
            }
            y++;
        }
        printf("\n");
		// printf("%d, command = |%s|\n", x, splited[x]);
	// }
}
void	input_prompt(void)
{
	char *input;
	int cmd_count;
	(void)cmd_count;
    (void)pipe;
	t_pipe *new_pipe;
	(void)new_pipe;
	
	while (1)
	{
		input = readline("minishell> ");
		add_history(input);
		if (validate_s_d_quote(input) == 1)
			continue;
		cmd_count = pipe_number(input) + 1;
		new_pipe = malloc(sizeof(t_pipe) * cmd_count);
		init_pipe(new_pipe, cmd_count, input);
		// printf("there are |%d| cmd\n", cmd_count);
		free(input);
	}
	
}

int main()
{
    input_prompt();
    return(0);
}