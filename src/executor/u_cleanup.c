/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cleanup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:24:03 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/19 23:05:20 by tnakas           ###   ########.fr       */
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
		arr[i] = NULL;
	}
	free(arr);
	arr = NULL;
}

/* this function invokes clean up
*  functions for the pipes and PIDs*/
void	free_pids_and_pipes(t_msh *info)
{
	free_arr_int(info->pipes, info->cmds_num - 1);
	free(info->pids);
	info->pipes = NULL;
	info->pids = NULL;
}

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
	arr = NULL;
}
