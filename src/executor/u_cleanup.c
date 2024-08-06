/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:24:03 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/05 21:08:17 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function frees allocated memory for an array
*  of 'int' pointers; the 'num' parameter specifies
*  the number of elements in the 'arr' array	  */
void	free_arr_int(int **arr, int num)
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
void	free_pids_and_pipes(t_msh *info)
{
	free_arr_int(info->pipes, info->cmds_num - 1);
	free(info->pids);
}

/* should we free here tokens_list ?*/
//void	free_all_prog_vars(t_msh *info)
//{
//	free_cmds_list();
//	free_env_vars_list();
//}

/* this function frees an array of strings */
void	free_arr_str(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
