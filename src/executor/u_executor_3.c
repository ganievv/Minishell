/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:49:23 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/19 04:53:23 by tnakas           ###   ########.fr       */
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

void	print_cmd_not_found(char *cmd)
{
	write(STDERR_FILENO, "msh: ", 5);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
}

void	reset_signals(void)
{
	change_terminal_echo_ctl(false);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	is_cmd_present_one_cmd(t_msh *info)
{
	int	exit_status;

	if (!info->cmds->command)
	{
		info->io_fds = save_io_fds(info->cmds);
		exit_status = make_files_redir(info->cmds);
		restore_io_fds(&(info->io_fds), info->cmds);
		exit_status = (exit_status == 0);
		info->last_exit_status = exit_status;
		return (0);
	}
	return (1);
}

void	is_cmd_present_multiple_cmds(t_pipe_group *cmd)
{
	int	exit_status;

	if (!cmd->command)
	{
		exit_status = make_files_redir(cmd);
		exit_status = (exit_status == 0);
		exit(exit_status);
	}
}
