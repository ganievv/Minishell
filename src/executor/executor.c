/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/27 20:59:27 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_multiple_cmds(int i, int cmd_ptr_i, t_msh *info)
{
	char	**envp_arr;
	char	**argv;
	char	*cmd_path;

	envp_arr = linked_list_to_arr(info->env_vars);
	argv = args_to_argv(info->cmds->args);
	info->pids[i] = fork();
	if (info->pids[i] == -1)
		return ;
	if (info->pids[i] == 0) /* child process*/
	{
		if (cmd_ptr_i >= 0)
			(info->builtin_ptrs[cmd_ptr_i])(info->cmds[i].args, &info->env_vars);
		else
		{
			cmd_path = search_cmd_path(info->cmds[i].command, info);
			if (execve(cmd_path, argv, envp_arr) == -1)
				perror("msh: "); /* what should I do in this case ?*/
		}
		return (0);
	}
	if (cmd_path)  /* when should I free it ?*/
		free(cmd_path);
}

static void	process_multiple_cmds(t_msh *info, int cmds_num)
{
	int		cmd_ptr_i;
	int		i;

	info->pids = (int *)malloc(sizeof(int) * cmds_num);
	if (!info->pids)
		return ;
	pipes_create(info, cmds_num);
	i = -1;
	while (++i < cmds_num)
	{
		make_redirections(&info->cmds[i]);
		cmd_ptr_i = is_cmd_builtin(info->cmds[i].command, info);
		exec_multiple_cmds(i, cmd_ptr_i, info);
	}
	wait_for_processes(info, cmds_num);
	clean_pids_and_pipes();
}

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

	make_redirections(&info->cmds[0]);
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
	info->cmds = count_cmds(info->cmds);
	if (info->cmds == 1)
		process_one_cmd(info);
	else
		process_multiple_cmds(info, info->cmds);
}
