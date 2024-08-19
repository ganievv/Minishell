/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:03:55 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/19 23:00:27 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function checks if a given command is a builtin command;
*
*  return values:
*				  '-1'   -> not a builtin cmd
*				  '>= 0' -> an index in the 'builtin_names' array
*							where the name of the command is found */
int	is_cmd_builtin(char *cmd, t_msh *info)
{
	char	*cmd_cp;
	int		i;

	i = -1;
	while (info->builtin_names[++i] != NULL)
	{
		if (ft_strcmp(cmd, info->builtin_names[i]) == 0)
			return (i);
	}
	i = -1;
	cmd_cp = str_to_lower_case(cmd);
	if (!cmd_cp)
		return (-1);
	while (info->builtin_names[++i] != NULL)
	{
		if (ft_strcmp(cmd_cp, info->builtin_names[i]) == 0)
			return (free(cmd_cp), i);
	}
	return (free(cmd_cp),cmd = NULL, -1);
}

/* this function counts how many
*  strings a given array has  */
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

/* this function counts the number of nodes in
*  a given linked list; the count represents
*  the total number of commands				*/
int	count_cmds(t_pipe_group *cmds)
{
	int	count;

	count = 0;
	while (cmds != NULL)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}
