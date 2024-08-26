/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_wait_for_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:41:25 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/18 15:57:10 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_sig(int wstatus)
{
	if (WTERMSIG(wstatus) == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (WTERMSIG(wstatus) == SIGQUIT)
		write(STDERR_FILENO, "Quit: 3\n", 8);
	return (128 + WTERMSIG(wstatus));
}

/* this function waits for all commands to finish
*  their execution; if it is the last command to
*  execute, it will save its exit status in the 
*  info->last_exit_status */
void	wait_for_processes(t_msh *info, int cmds_num)
{
	int	i;
	int	wstatus;
	int	estatus;
	int	child_pid;

	i = -1;
	while (++i < cmds_num)
	{
		child_pid = wait(&wstatus);
		if (child_pid == info->pids[cmds_num - 1])
		{
			if (WIFEXITED(wstatus))
			{
				estatus = WEXITSTATUS(wstatus);
				info->last_exit_status = estatus;
			}
			else if (WIFSIGNALED(wstatus))
				info->last_exit_status = check_sig(wstatus);
		}
	}
}
