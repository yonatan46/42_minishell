/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 20:17:59 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/13 20:23:11 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ultimate_free: is a function that free mostly everything 
 * that we have
 * @data: the structure containing infor about the whole execution
 * @pipe: an array of structs containing info of all the execution
*/
void	ultimate_free(t_data *data, t_pipe *pipe)
{
	int	x;

	x = 0;
	while (x < pipe[data->index].cmd_len)
	{
		free(pipe[x].cmd);
		free_func(pipe[x].arg);
		free_func(pipe[x].f_cmd);
		x++;
	}
	free_list(*data->head);
	free(data->head);
	free(pipe);
}
