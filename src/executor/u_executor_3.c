/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 21:24:03 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/29 15:36:11 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
