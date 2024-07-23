/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/23 20:44:35 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exec_external_cmd(t_msh *info)
{
}

static int	exec_one_cmd(t_msh *info)
{
	int	i;

	i = 0;
	while (info->builtin_names[i] != NULL)
	{
		if (strcmp(info->cmds, info->builtin_names[i]) == 0)
			return ((info->builtin_ptrs[i])(info->cmds->args));
		i++;
	}

	return (exec_external_cmd(group));
}

int	exec_all_cmds(t_msh *info)
{
	init_builtin_names(info->builtin_names);
	init_builtin_ptrs(info->builtin_ptrs);
	if (count_cmds(info->cmds) == 1)
		exec_one_cmd(info);
	else
	{
		while (info->groups != NULL)
		{
			info->groups = info->groups->next;
		}
	}
}
