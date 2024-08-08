/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/06 20:36:50 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function converts command 'args' to 'argv'; creates a new process
*  to execute a command and handles pipes and file redirections */
static int	exec_multiple_cmds(int i, t_msh *info, char **envp)
{
	int	cmd_ptr_i;

	info->pids[i] = fork();
	if (info->pids[i] == -1)
		return (1);
	if (info->pids[i] == 0)
	{
		make_pipes_redir(info, i);
		make_files_redir(&info->cmds[i]);
		cmd_ptr_i = is_cmd_builtin(info->cmds[i].command, info);
		if (cmd_ptr_i >= 0)
			return ((info->builtin_ptrs[cmd_ptr_i])(info->cmds[i].args,
				&envp, info));
		else
		{
			info->cmds[i].cmd_path = search_cmd_path(info->cmds[i].command,
					info);
			info->cmds[i].argv = args_to_argv(info->cmds[i].args,
					info->cmds[i].cmd_path);
			execve(info->cmds[i].cmd_path, info->cmds[i].argv, envp);
			perror("msh: ");
			exit(EXIT_FAILURE);
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
	char	**envp_buf;
	int		i;

	envp_buf = info->envp;
	info->pids = (int *)malloc(sizeof(int) * cmds_num);
	if (!info->pids)
		return ;
	pipes_create(info, cmds_num);
	i = -1;
	while (++i < cmds_num)
		exec_multiple_cmds(i, info, envp_buf);
	close_all_pipes(info->pipes, cmds_num - 1);
	wait_for_processes(info, cmds_num);
	free_pids_and_pipes(info);
}

/* this function creates a new process, performs
*  redirection and executes a command there	  */
static void	exec_one_cmd(char *cmd_path, t_msh *info)
{
	char	**argv;
	int		pid;

	argv = args_to_argv(info->cmds[0].args, cmd_path);
	pid = fork();
	if (pid == 0)
	{
		make_files_redir(&info->cmds[0]);
		execve(cmd_path, argv, info->envp);
		perror("msh: ");
		exit(EXIT_FAILURE);
	}
	wait_for_processes(info, info->cmds_num);
	free_arr_str(argv);
}

/* this function executes a command in the shell process if it is a
*  builtin command, or invokes a function to create and execute an
*  external command in a new process;
*  this function is only executed when the number of commands is 1*/
static void	process_one_cmd(t_msh *info)
{
	char	*cmd_path;
	int		index;

	index = is_cmd_builtin(info->cmds[0].command, info);
	if (index >= 0)
	{
		make_files_redir(&info->cmds[0]);
		info->last_exit_status = (info->builtin_ptrs[index])
			(info->cmds[0].args, &info->envp, info);
	}
	else
	{
		cmd_path = search_cmd_path(info->cmds[0].command, info);
		exec_one_cmd(cmd_path, info);
		if (cmd_path)
			free(cmd_path);
	}
}

/* this function launches all commands from
* 'info->cmds' linked list				 */
void	exec_all_cmds(t_msh *info)
{
	init_builtin_names(info->builtin_names);
	init_builtin_ptrs(info->builtin_ptrs);
	info->envp = copy_arr_str(info->envp);
	info->cmds_num = count_cmds(info->cmds);
	if (info->cmds_num == 1)
		process_one_cmd(info);
	else
		process_multiple_cmds(info, info->cmds_num);
	//free_all_prog_vars(info);
}
