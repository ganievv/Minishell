/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/25 20:32:39 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_external_cmd(t_msh *info)
{
	char	*path_env_v;

	path_env_v = search_env_var(info->env_vars, "PATH");
	if (!path_env_v)
		return (1);
}

static int	exec_one_cmd(t_msh *info)
{
	int	index;

	if (info->cmds->file)
		;
	index = is_cmd_builtin(info->cmds->command, info);
	if (index >= 0)
		(info->builtin_ptrs[index])(info->cmds->args, &info->env_vars);
	else
		exec_external_cmd(info);
}

int	exec_all_cmds(t_msh *info)
{
	init_builtin_names(info->builtin_names);
	init_builtin_ptrs(info->builtin_ptrs);
	init_env_vars_list(info);
	if (count_cmds(info->cmds) == 1)
		exec_one_cmd(info);
	else
	{
		while (info->cmds != NULL)
		{
			info->cmds = info->cmds->next;
		}
	}
}
