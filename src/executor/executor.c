/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/26 19:01:44 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_cmd(char *absolute_path, char **args, t_env_vars *envp)
{
	char	**envp_arr;
	char	**argv;

	envp_arr = linked_list_to_arr(envp);
	argv = args_to_argv(args);
	execve(absolute_path, argv, envp_arr);
}

/* this function executes an external command in a new process;
*  it first searches for the command's executable in the 'PATH'
*  environment variable; if the executable is not found there,
*  the function assumes the command has an absolute path and
*  executes it directly										 */
static int	launch_external_cmd(char *cmd, t_msh *info)
{
	char	*path_env_v;
	char	*dir_of_exec;
	char	*absolute_path;

	dir_of_exec = NULL;
	path_env_v = search_env_var(info->env_vars, "PATH");
	if (path_env_v)
		dir_of_exec = search_exec_dir(cmd, (ft_strchr(path_env_v, '=') + 1));
	if (dir_of_exec)
	{
		absolute_path = ft_strjoin(dir_of_exec, cmd);
		free(dir_of_exec);
	}
	else
		absolute_path = ft_strdup(cmd);
	exec_cmd(absolute_path, info->cmds->args, info->env_vars);
	if (absolute_path)
		free(absolute_path);
}

/* this function executes one command;
*  it does not create a new process if
*  this command is a builtin		*/
static int	launch_one_cmd(t_msh *info)
{
	int	index;

	if (info->cmds->file)
		make_redirection(info->cmds);
	index = is_cmd_builtin(info->cmds->command, info);
	if (index >= 0)
		(info->builtin_ptrs[index])(info->cmds->args, &info->env_vars);
	else
		launch_external_cmd(info->cmds->command, info);
}

/* this function launches all commands from
* 'info->cmds' linked list				 */
int	exec_all_cmds(t_msh *info)
{
	init_builtin_names(info->builtin_names);
	init_builtin_ptrs(info->builtin_ptrs);
	init_env_vars_list(info);
	if (count_cmds(info->cmds) == 1)
		launch_one_cmd(info);
	else
	{
		while (info->cmds != NULL)
		{
			info->cmds = info->cmds->next;
		}
	}
}
