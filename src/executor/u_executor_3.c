/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:24:03 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/29 19:51:22 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function frees allocated memory for an array
*  of 'int' pointers; the 'num' parameter specifies
*  the number of elements in the 'arr' array	  */
void	free_int_arr(int **arr, int num)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (++i < num)
	{
		if (arr[i])
			free(arr[i]);
	}
	free(arr);
}

/* this function invokes clean up
*  functions for the pipes and PIDs*/
void	clean_pids_and_pipes(t_msh *info)
{
	free_int_arr(info->pipes, info->cmds_num - 1);
	free(info->pids);
}

void	free_all_prog_vars(t_msh *info)
{
	free_tokens_list();
	free_cmds_list();
	free_env_vars_list();
	/* 'info->builtin_names' arr*/
	/* 'info->builtin_ptrs' arr*/
}
