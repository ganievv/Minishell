/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/26 18:30:37 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function executes an external command in a new process;
*  it first searches for the command's executable in the 'PATH'
*  environment variable; if the executable is not found there,
*  the function assumes the command has an absolute path and
*  executes it directly										 */
static int	exec_external_cmd(char *cmd, t_msh *info)
{
	char	*path_env_v;
	char	*dir_of_exec;

	dir_of_exec = NULL;
	path_env_v = search_env_var(info->env_vars, "PATH");
	if (path_env_v)
		dir_of_exec = search_exec_dir(cmd, (ft_strchr(path_env_v, '=') + 1));
	if (!dir_of_exec)
		dir_of_exec = cmd;
	int	id = fork();
	if (id == 0)
	{
		return (0);
	}
}

/* this function executes one command;
*  it does not create a new process if
*  this command is a builtin		*/
static int	exec_one_cmd(t_msh *info)
{
	int	index;

	if (info->cmds->file)
		make_redirection();
	index = is_cmd_builtin(info->cmds->command, info);
	if (index >= 0)
		(info->builtin_ptrs[index])(info->cmds->args, &info->env_vars);
	else
		exec_external_cmd(info->cmds->command, info);
}

/* this function launches all commands from
* 'info->cmds' linked list				 */
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
