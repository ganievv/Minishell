/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/27 17:03:39 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function creates a new process and executes
*  a command there using 'cmd_path', which is
*  the path to the command executable file		 */
static void	exec_one_cmd(char *cmd_path, t_msh *info)
{
	char	**envp_arr;
	char	**argv;
	int		pid;

	envp_arr = linked_list_to_arr(info->env_vars);
	argv = args_to_argv(info->cmds->args);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, argv, envp_arr) == -1)
			perror("msh: "); /* what should I do in this case ?*/
	}
	wait(NULL);
}

/* this function performs redirection, executes a command in the shell
*  process if it is a builtin command, or invokes a function to create
*  and execute an external command in a new process;
*  this function is only executed when the number of commands is 1	*/
static int	process_one_cmd(t_msh *info)
{
	char	*cmd_path;
	int		index;

	if (info->cmds->file_in)
		make_redirection(info->cmds->file_in, info->cmds->redir_in,
			info->cmds->mode_in);
	if (info->cmds->file_out)
		make_redirection(info->cmds->file_out, info->cmds->redir_out,
			info->cmds->mode_out);
	index = is_cmd_builtin(info->cmds->command, info);
	if (index >= 0)
		(info->builtin_ptrs[index])(info->cmds->args, &info->env_vars);
	else
	{
		cmd_path = search_cmd_path(info->cmds->command, info);
		exec_one_cmd(cmd_path, info);
		if (cmd_path)
			free(cmd_path);
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
