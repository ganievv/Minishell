/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/26 22:22:58 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_one_cmd(char *absolute_path, t_msh *info)
{
	char	**envp_arr;
	char	**argv;
	int		pid;

	envp_arr = linked_list_to_arr(info->env_vars);
	argv = args_to_argv(info->cmds->args);
	pid = fork();
	if (pid == 0)
		execve(absolute_path, argv, envp_arr);	
	wait(NULL);
}

/* this function makes redirection, executes a command in
*  a shell process if it is builtin command or execute it
*  in a new process if it is a external command		 */
static int	process_one_cmd(t_msh *info)
{
	char	*absolute_path;
	int		index;

	if (info->cmds->file)
		make_redirection(info->cmds);
	index = is_cmd_builtin(info->cmds->command, info);
	if (index >= 0)
		(info->builtin_ptrs[index])(info->cmds->args, &info->env_vars);
	else
	{
		absolute_path = find_absolute_path(info->cmds->command, info);
		exec_one_cmd(absolute_path, info);
		if (absolute_path)
			free(absolute_path);
	}
}

/* this function launches all commands from
* 'info->cmds' linked list				 */
int	exec_all_cmds(t_msh *info)
{
	init_builtin_names(info->builtin_names);
	init_builtin_ptrs(info->builtin_ptrs);
	init_env_vars_list(info);
	if (count_cmds(info->cmds) == 1)
		process_one_cmd(info);
	else
	{
		while (info->cmds != NULL)
		{
			info->cmds = info->cmds->next;
		}
	}
}
