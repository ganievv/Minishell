/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_files_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:54:08 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/17 15:19:20 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_heredoc(t_pipe_group *cmd)
{
	int	p[2];

	if (pipe(p) == -1)
		return (0);
	if (write(p[1], cmd->heredoc_strs, ft_strlen(cmd->heredoc_strs)) == -1)
	{
		close(p[0]);
		close(p[1]);
		return (0);
	}
	close(p[1]);
	if (dup2(p[0], STDIN_FILENO) == -1)
	{
		close(p[0]);
        return (0);
	}
	close(p[0]);
	return (1);
}

/* this function handles redirections for an input
*  file and an output file, if they exist		*/
int	make_files_redir(t_pipe_group *cmd)
{
	int	fd;

	if (cmd->is_heredoc_in)
	{
		if (!redir_heredoc(cmd))
			return (0);
	}
	else if (cmd->file_in)
	{
		fd = open(cmd->file_in, cmd->mode_in);
		if (fd == -1)
			return (perror(cmd->file_in), 0);
		dup2(fd, cmd->redir_in);
		close(fd);
	}
	if (cmd->file_out)
	{
		fd = open(cmd->file_out, cmd->mode_out, 0666);
		if (fd == -1)
			return (perror(cmd->file_out), 0);
		dup2(fd, cmd->redir_out);
		close(fd);
	}
	return (1);
}

int	*save_io_fds(t_pipe_group *cmd)
{
	int	*fds;

	fds = (int *)malloc(sizeof(int) * 2);
	if (!fds)
		return (NULL);
	if (cmd->file_in || cmd->is_heredoc_in)
		fds[0] = dup(cmd->redir_in);
	if (cmd->file_out)
		fds[1] = dup(cmd->redir_out);
	return (fds);
}

void	restore_io_fds(int *fds, t_pipe_group *cmd)
{
	if (!fds)
		return ;
	if (cmd->file_in || cmd->is_heredoc_in)
	{
		dup2(fds[0], cmd->redir_in);
		close(fds[0]);
	}
	if (cmd->file_out)
	{
		dup2(fds[1], cmd->redir_out);
		close(fds[1]);
	}
	free(fds);
}
