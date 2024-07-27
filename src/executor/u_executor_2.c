/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:59:51 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/27 19:55:39 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_cmd_path(char *cmd, t_msh *info)
{
	char	*path_env_v;
	char	*dir_of_exec;
	char	*cmd_path;

	dir_of_exec = NULL;
	path_env_v = search_env_var(info->env_vars, "PATH");
	if (path_env_v)
		dir_of_exec = search_exec_dir(cmd, (ft_strchr(path_env_v, '=') + 1));
	if (dir_of_exec)
	{
		cmd_path = ft_strjoin(dir_of_exec, cmd);
		free(dir_of_exec);
	}
	else
		cmd_path = ft_strdup(cmd);
	return (cmd_path);
}

void	make_redirections(t_pipe_group *cmd)
{
	int	fd;

	if (cmd->file_in)
	{
		fd = open(cmd->file_in, cmd->mode_in); /* what permissioms should I specify ?*/
		if (fd == -1)
			return ;
		dup2(fd, cmd->redir_in);
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

char	**linked_list_to_arr(t_env_vars *list)
{
}

char	**args_to_argv(char **args)
{
}
