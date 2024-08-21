/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_files_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:54:08 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/21 14:26:30 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redir_heredoc(t_pipe_group *cmd)
{
	int	p[2];

	if (pipe(p) == -1)
		return (0);
	if (!cmd->heredoc_strs || write(p[1], cmd->heredoc_strs,
			ft_strlen(cmd->heredoc_strs)) == -1)
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
	if (cmd->is_heredoc_in)
	{
		if (!redir_heredoc(cmd))
			return (0);
	}
	if (!process_in_files(cmd->f_in))
		return (0);
	if (!process_out_files(cmd->f_out))
		return (0);
	return (1);
}

int	*save_io_fds(t_pipe_group *cmd)
{
	int	*fds;

	fds = (int *)malloc(sizeof(int) * 2);
	if (!fds)
		return (NULL);
	if (cmd->f_in || cmd->is_heredoc_in)
		fds[0] = dup(STDIN_FILENO);
	if (cmd->f_out)
		fds[1] = dup(STDOUT_FILENO);
	return (fds);
}

void	restore_io_fds(int **fds, t_pipe_group *cmd)
{
	if (!fds || !*fds)
		return ;
	if (cmd->f_in || cmd->is_heredoc_in)
	{
		dup2((*fds)[0], STDIN_FILENO);
		close((*fds)[0]);
	}
	if (cmd->f_out)
	{
		dup2((*fds)[1], STDOUT_FILENO);
		close((*fds)[1]);
	}
	free(*fds);
	(*fds) = NULL;
}
