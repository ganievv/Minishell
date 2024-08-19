/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/18 15:43:16 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function converts command 'args' to 'argv'; creates a new process
*  to execute a command and handles pipes and file redirections */
static int	exec_multiple_cmds(int i, t_msh *info,
	char **envp, t_pipe_group *cmd)
{
	int	cmd_ptr_i;

	cmd->cmd_path = search_cmd_path(cmd->command, info);
	cmd->argv = args_to_argv(cmd->args, cmd->cmd_path);
	info->pids[i] = fork();
	if (info->pids[i] == -1)
		return (1);
	if (info->pids[i] == 0)
	{
		is_cmd_present_multiple_cmds(cmd);
		reset_signals();
		make_pipes_redir(info, i);
		if (!make_files_redir(cmd))
			exit(1);
		cmd_ptr_i = is_cmd_builtin(cmd->command, info);
		if (cmd_ptr_i >= 0)
			exit((info->builtin_ptrs[cmd_ptr_i])(cmd->args, &envp, info));
		else
		{
			execve(cmd->cmd_path, cmd->argv, envp);
			print_cmd_not_found(cmd->cmd_path);
			exit(CMD_NOT_FOUND);
		}
	}
	return (0);
}

/* this function allocates memory for PIDs of processes; invokes a
*  function to allocate memory for pipes array; invokes a function
*  in a loop for each command to execute it in a new process;
*  invokes a function to close all pipes for the shell process;
*  invokes a function to wait for each command to finish; invokes a
*  function to clean up an array of PIDs and pipes				 */
static void	process_multiple_cmds(t_msh *info, int cmds_num)
{
	t_pipe_group	*cmd;
	char			**envp_buf;
	int				i;

	envp_buf = info->envp;
	info->pids = (int *)malloc(sizeof(int) * cmds_num);
	if (!info->pids)
		return ;
	if (!pipes_create(info, cmds_num))
		return ;
	i = -1;
	cmd = info->cmds;
	while ((++i < cmds_num) && cmd)
	{
		exec_multiple_cmds(i, info, envp_buf, cmd);
		cmd = cmd->next;
	}
	close_all_pipes(info->pipes, cmds_num - 1);
	wait_for_processes(info, cmds_num);
}

/* this function creates a new process, performs
*  redirection and executes a command there	  */
static void	exec_one_cmd(t_msh *info)
{
	info->pids = (int *)malloc(sizeof(int) * info->cmds_num);
	if (!info->pids)
		return ;
	info->cmds->cmd_path = search_cmd_path(info->cmds->command, info);
	info->cmds->argv = args_to_argv(info->cmds->args, info->cmds->cmd_path);
	info->pids[0] = fork();
	if (info->pids[0] == 0)
	{
		reset_signals();
		if (!make_files_redir(info->cmds))
			exit(1);
		execve(info->cmds->cmd_path, info->cmds->argv, info->envp);
		print_cmd_not_found(info->cmds->cmd_path);
		exit(CMD_NOT_FOUND);
	}
}

/* this function executes a command in the shell process if it is a
*  builtin command, or invokes a function to create and execute an
*  external command in a new process;
*  this function is only executed when the number of commands is 1*/
static void	process_one_cmd(t_msh *info)
{
	int	index;
	int	*fds;

	if (!is_cmd_present_one_cmd(info))
		return ;
	index = is_cmd_builtin(info->cmds->command, info);
	if (index >= 0)
	{
		fds = save_io_fds(info->cmds);
		if (!make_files_redir(info->cmds))
		{
			info->last_exit_status = 1;
			return ;
		}
		info->last_exit_status = (info->builtin_ptrs[index])
			(info->cmds->args, &(info->envp), info);
		restore_io_fds(fds, info->cmds);
	}
	else
	{
		exec_one_cmd(info);
		wait_for_processes(info, info->cmds_num);
	}
}

/* this function launches all commands from
* 'info->cmds' linked list				 */
void	exec_all_cmds(t_msh *info)
{
	info->cmds_num = count_cmds(info->cmds);
	if (info->cmds_num == 1)
		process_one_cmd(info);
	else
		process_multiple_cmds(info, info->cmds_num);
}
