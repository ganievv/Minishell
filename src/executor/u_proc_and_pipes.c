/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_proc_and_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:52:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/27 18:02:17 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipes_close(t_msh *info, int cmds_num)
{
}

void	wait_for_processes(t_msh *info, int cmds_num)
{
	int	i;

	i = -1;
	while (++i < cmds_num)
		wait(NULL);
}

void	pipes_create(t_msh *info, int cmds_num)
{
	int	pipes_num;
	int	i;

	i = -1;
	pipes_num = cmds_num - 1;
	info->pipes = (int **)malloc(sizeof(int *) * pipes_num);
	while (++i < pipes_num)
		info->pipes[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < cmds_num)
	{
		if (pipe(info->pipes[i]) == -1)
			return ;
	}
}

