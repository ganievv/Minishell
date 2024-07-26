/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_processes_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:52:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/26 20:59:55 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipes_create(t_msh *info, int cmds_num)
{
	int	i;

	i = -1;
	info->pipes = (int **)malloc(sizeof(int *) * cmds_num);
	while (++i < cmds_num)
		info->pipes[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < cmds_num)
	{
		if (pipe(info->pipes[i]) == -1)
			return ;
	}
}

void	processes_create(t_msh *info, int cmds_num)
{
	int	i;

	info->pids = (int *)malloc(sizeof(int) * cmds_num);
	i = -1;
	while (++i < cmds_num)
	{
		info->pids[i] = fork();
		if (info->pids[i] == -1)
			break ;
		if (info->pids[i] == 0)
		{
			return (0);
		}
	}
}

void	wait_for_processes(t_msh *info, int cmds_num)
{
	int	i;

	i = -1;
	while (++i < cmds_num)
		wait(NULL);
}
