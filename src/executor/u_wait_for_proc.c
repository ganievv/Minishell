/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_wait_for_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:41:25 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/31 19:32:29 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function waits for all commands to finish
*  their execution; if it is the last command to
*  execute, it will save its exit status in the 
*  info->last_exit_status */
void	wait_for_processes(t_msh *info, int cmds_num)
{
	int	i;
	int	wstatus;
	int	estatus;

	i = -1;
	while (++i < cmds_num)
	{
		if (i != cmds_num - 1)
			wait(NULL);
		else
		{
			wait(&wstatus);
			if (WIFEXITED(wstatus))
				estatus = WEXITSTATUS(wstatus);
			info->last_exit_status = estatus;
		}
	}
}
