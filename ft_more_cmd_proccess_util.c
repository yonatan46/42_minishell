/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_cmd_proccess_util.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:18:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/15 17:34:06 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * first_process_util: 
*/
void	first_process_util(t_data *proc, t_pipe *av, char **envp)
{
	char	*tmp;

	if (av[0].cmd && proc->check > 0)
		check_built_ins_and_exexute(proc, av, envp);
	tmp = parsing(proc, envp, av[0].cmd);
	if (av[0].cmd && tmp && av[0].cmd[0])
	{
		execve(tmp, av[0].arg, envp);
		free_func_one_cmd(av, proc, envp);
	}
	else
		cmd_not_found(av, proc, 0);
}

void	last_process_util(t_data *proc, t_pipe *av, char **envp)
{
	char	*tmp;

	tmp = parsing(proc, envp, av[av->cmd_len - 1].cmd);
	if (av[av->cmd_len - 1].cmd && tmp && av[av->cmd_len - 1].cmd[0])
	{
		execve(tmp, av[av->cmd_len - 1].arg, envp);
		free_func_one_cmd(av, proc, envp);
	}
	else
		cmd_not_found(av, proc, av->cmd_len - 1);
}
