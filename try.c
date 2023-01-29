#include <stdio.h>
#include <string.h>
#include "minishell.h"
/**
 * just a simple try function with main to 
 * try functions before adding it to the codespace
*/

// void ft_linked_env(t_list **head, char **env, int shl_lvl)
// {
// 	int x = -1;
// 	int index_pwd = 0;
// 	int index_shllvl = 0;
// 	// int index_env = 0;
// 	char pwd[100];

// 	while (env[++x])
// 	{
// 		if (strncmp(env[x], "PWD", 3) == 0)
// 		{
// 			ft_lstadd_back(head, ft_lstnew(ft_strjoin("minePWD=",getcwd(pwd, 100)), x));
// 			index_pwd = x;
// 			continue;
// 		}
// 		else if (strncmp(env[x], "SHLVL", 5) == 0)
// 		{
// 			index_shllvl = 1;
// 			continue;
// 		}
// 		else if (strncmp(env[x], "_=", 2) == 0)
// 		{
// 			ft_lstadd_back(head, ft_lstnew("_=env", x));
// 			continue;
// 		}
// 		ft_lstadd_back(head, ft_lstnew(env[x], x));
// 	}
// 	if (!*head)
// 	{
// 		ft_lstadd_back(head, ft_lstnew(ft_strjoin("PWD=",getcwd(pwd, 100)), 0));
// 		ft_lstadd_back(head, ft_lstnew(ft_strjoin("SHLVL=",ft_itoa(shl_lvl)), 1));
// 		ft_lstadd_back(head, ft_lstnew("_=env", 2));
// 		// printf("created |%d| %s\n", (*head)->index, (*head)->content);
// 		// printf("created |%d| %s\n", (*head)->next->index, (*head)->next->content);
// 		// printf("created |%d| %s\n", (*head)->next->next->index, (*head)->next->next->content);
// 	}
// 	// else
// 	// {
// 	// 	while ((*head))
// 	// 	{
// 	// 		printf("index|%d| %s\n", (*head)->index, (*head)->content);
// 	// 		(*head) = (*head)->next;
// 	// 	}
// 	// }
// 	// while (tmp)
// 	// {
// 	// 	printf(" tmp |%d| %s\n", tmp->index, tmp->content);
// 	// 	tmp = tmp->next;
// 	// }
// 	// printf("len of env |%d|\n", x);
// }

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int s;
	int res = 1001;
	s = res;
	s = 42;
	printf("s |%d|\n", s);
	printf("res |%d|\n", res);
	char *str[] = {"/usr/bin/grep", "main", "main.c", NULL};
	execve(str[0], str, env);
}