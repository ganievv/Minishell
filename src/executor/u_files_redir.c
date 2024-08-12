/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_files_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:54:08 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/12 18:17:58 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	redir_heredoc(int *p)
{
	dup2(p[0], STDIN_FILENO);
	close(p[0]);
}

/* this function handles redirections for an input
*  file and an output file, if they exist		*/
int	make_files_redir(t_pipe_group *cmd)
{
	int	fd;

	if (cmd->is_heredoc_in)
		redir_heredoc(cmd->heredoc_p);
	else if (cmd->file_in)
	{
		fd = open(cmd->file_in, cmd->mode_in);
		if (fd == -1)
			return (perror("msh"), 0);
		dup2(fd, cmd->redir_in);
		close(fd);
	}
	if (cmd->file_out)
	{
		fd = open(cmd->file_out, cmd->mode_out, 0666);
		if (fd == -1)
			return (perror("msh"), 0);
		dup2(fd, cmd->redir_out);
		close(fd);
	}
	return (1);
}
