/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_proc_and_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 20:52:13 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/31 18:44:00 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function handles redirections for an input
*  file and an output file, if they exist		*/
void	make_files_redir(t_pipe_group *cmd)
{
	int	fd;

	if (cmd->file_in)
	{
		fd = open(cmd->file_in, cmd->mode_in); /* what permissioms should I specify ?*/
		if (fd == -1)
			return ;
		dup2(fd, cmd->redir_in); /* is that correct order of fds ?*/
		close(fd);
	}
	if (cmd->file_out)
	{
		fd = open(cmd->file_out, cmd->mode_out); /* what permissioms should I specify ?*/
		if (fd == -1)
			return ;
		dup2(fd, cmd->redir_out);
		close(fd);
	}
}

/* this function closes all unused pipes for the command with
*  the specified 'cmd_index'; it ensures that only the pipes
*  relevant to the command at 'cmd_index' are kept open	   */
static void	cmd_pipes_close(t_msh *info, int cmd_index)
{
	int	i;

	i = -1;
	while (++i < info->cmds_num - 1)
	{
		if (cmd_index == 0)
		{
			close(info->pipes[i][0]);
			if (i != cmd_index)
				close(info->pipes[i][1]);
		}
		else if (cmd_index != info->cmds_num - 1)
		{
			if (i != (cmd_index - 1))
				close(info->pipes[i][0]);
			if (i != cmd_index)
				close(info->pipes[i][1]);
		}
		else
		{
			close(info->pipes[i][1]);
			if (i != (cmd_index - 1))
				close(info->pipes[i][0]);
		}
	}
}

/* this function allocates memory for the pipes and
*  opens them; it creates `cmds_num - 1` pipes, each
*  represented by an array of two integers		 */
int	pipes_create(t_msh *info, int cmds_num)
{
	int	pipes_num;
	int	i;

	i = -1;
	pipes_num = cmds_num - 1;
	info->pipes = (int **)malloc(sizeof(int *) * pipes_num);
	while (++i < pipes_num)
		info->pipes[i] = (int *)malloc(sizeof(int) * 2);
	i = -1;
	while (++i < pipes_num)
	{
		if (pipe(info->pipes[i]) == -1)
		{
			i = -1;
			while (++i < pipes_num)
			{
				close(info->pipes[i][0]);
				close(info->pipes[i][1]);
			}
			return (free_arr_int(info->pipes, pipes_num), 0);
		}
	}
	return (1);
}

/* this function handles redirection of standard input
*  and output to the write and read ends of pipes	*/
void	make_pipes_redir(t_msh *info, int cmd_index)
{
	cmd_pipes_close(info, cmd_index);
	if (cmd_index == 0)
	{
		dup2(info->pipes[cmd_index][1], STDOUT_FILENO);
		close(info->pipes[cmd_index][1]);
	}
	else if (cmd_index != info->cmds_num - 1)
	{
		dup2(info->pipes[cmd_index][1], STDOUT_FILENO);
		dup2(info->pipes[cmd_index - 1][0], STDIN_FILENO);
		close(info->pipes[cmd_index][1]);
		close(info->pipes[cmd_index - 1][0]);
	}
	else
	{
		dup2(info->pipes[cmd_index - 1][0], STDIN_FILENO);
		close(info->pipes[cmd_index - 1][0]);
	}
}
