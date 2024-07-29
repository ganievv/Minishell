/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:59:51 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/29 19:28:14 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function searches for the directory of a command (char *cmd)
*  in the 'PATH' environment variable.
*
*  return values:
*				  [path to a command] - a string which consists of [dir + cmd];
*				  [copy of a command] - if there is no executable file in the
*										directories of 'PATH' (meaning that it
*										was already an executable with its path)
*				  NULL                - if it failed to allocate memory*/
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

/* this function counts the number of
*  environment variables in the linked
*  list (t_env_vars *list)			*/
int	env_vars_count(t_env_vars *list)
{
	int	num;

	num = 0;
	while (list)
	{
		num++;
		list = list->next;
	}
	return (num);
}

/* this function converts the linked list of environment
*  variables (info->env_vars) to an array of strings (char **) */
char	**linked_list_to_arr(t_env_vars *list)
{
	char	**envp_arr;
	int		num;
	int		i;

	num = env_vars_count(list) + 1;
	envp_arr = (char **)malloc(sizeof(char *) * num);
	if (!envp_arr)
		return (NULL);
	i = 0;
	while (list)
	{
		envp_arr[i] = ft_strdup(list->var);
		if (!envp_arr[i++])
			return (free_arr_str(envp_arr), NULL);
		list = list->next;
	}
	envp_arr[i] = NULL;
	return (envp_arr);
}

/* this function converts command arguments 'args' to an
*  'argv' list, adding the file name to the [0] element */
char	**args_to_argv(char **args, char *cmd_path)
{
	char	**argv;
	int		num;
	int		i;

	i = 0;
	num = count_args(args) + 2;
	argv = (char **)malloc(sizeof(char *) * num);
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd_path);
	if (!argv[0])
		return (free(argv), NULL);
	while (args[i])
	{
		argv[i + 1] = ft_strdup(args[i]);
		if (argv[i + 1] == NULL)
			return (free_arr_str(argv), NULL);
		i++;
	}
	return (argv);
}
