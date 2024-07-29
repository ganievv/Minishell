/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_proc_and_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:52:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/29 18:43:44 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	pipes_close(t_msh *info, int cmd_index)
{
	int	i;

	i = -1;
	while (++i < info->cmds_num - 1)
	{
		if (cmd_index == 0)
		{
			close(info->pipes[i][0]);
			if (i != cmd_index)
				close(info->pipes[i][1]);
		}
		else if (cmd_index != info->cmds_num - 1)
		{
			if (i != (cmd_index - 1))
				close(info->pipes[i][0]);
			if (i != cmd_index)
				close(info->pipes[i][1]);
		}
		else
		{
			close(info->pipes[i][1]);
			if (i != (cmd_index - 1))
				close(info->pipes[i][0]);
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

int	pipes_create(t_msh *info, int cmds_num)
{
	int	pipes_num;
	int	i;

	i = -1;
	pipes_num = cmds_num - 1;
	info->pipes = (int **)malloc(sizeof(int *) * pipes_num);
	while (++i < pipes_num)
		info->pipes[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < pipes_num)
	{
		if (pipe(info->pipes[i]) == -1)
		{
			i = -1;
			while (++i < pipes_num)
			{
				close(info->pipes[i][0]);
				close(info->pipes[i][1]);
			}
			return (free_int_arr(info->pipes, pipes_num), 0);
		}
	}
	return (1);
}

void	make_pipes_redir(t_msh *info, int cmd_index)
{
	pipes_close(info, cmd_index);
	if (cmd_index == 0)
	{
		dup2(info->pipes[cmd_index][1], STDOUT_FILENO);
		close(info->pipes[cmd_index][1]);
	}
	else if (cmd_index != info->cmds_num - 1)
	{
		dup2(info->pipes[cmd_index][1], STDOUT_FILENO);
		dup2(info->pipes[cmd_index - 1][0], STDIN_FILENO);
		close(info->pipes[cmd_index][1]);
		close(info->pipes[cmd_index - 1][0]);
	}
	else
	{
		dup2(info->pipes[cmd_index - 1][0], STDIN_FILENO);
		close(info->pipes[cmd_index - 1][0]);
	}
}
