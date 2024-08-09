/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:49:23 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/09 22:06:51 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*str_to_lower_case(const char *cmd)
{
	char	*cmd_cp;
	int		i;

	i = -1;
	cmd_cp = ft_strdup(cmd);
	while (cmd_cp && cmd_cp[++i])
		cmd_cp[i] = ft_tolower(cmd_cp[i]);
	return (cmd_cp);
}

int	*save_io_fds(t_pipe_group *cmd)
{
	int	*fds;

	fds = (int *)malloc(sizeof(int) * 2);
	if (!fds)
		return (NULL);
	if (cmd->file_in)
		fds[0] = dup(cmd->redir_in);
	if (cmd->file_out)
		fds[1] = dup(cmd->redir_out);
	return (fds);
}

void	restore_io_fds(int *fds, t_pipe_group *cmd)
{
	if (!fds)
		return ;
	if (cmd->file_in)
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

void	print_cmd_not_found(char *cmd)
{
	write(STDERR_FILENO, "msh: ", 5);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
}
