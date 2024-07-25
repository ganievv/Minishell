/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:31:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/25 20:32:43 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function checks if a given command is a builtin;
*
*  return values:
*				  '-1'   -> not a builtin cmd
*				  '>= 0' -> a builtin cmd			  */
int	is_cmd_builtin(char *cmd, t_msh *info)
{
	int	i;

	i = 0;
	while (info->builtin_names[i] != NULL)
	{
		if (strcmp(cmd, info->builtin_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
