/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:59:51 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/07 14:50:43 by sganiev          ###   ########.fr       */
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
	char	*absolute_path;
	int		cmd_i;

	if (!cmd)
		return (NULL);
	absolute_path = NULL;
	cmd_i = search_env_var("PATH", info->envp);
	if (cmd_i != -1)
		absolute_path = search_exec_dir(cmd, info->envp[cmd_i]);
	if (!absolute_path)
		absolute_path = ft_strdup(cmd);
	return (absolute_path);
}

/* this function converts command arguments 'args' to an
*  'argv' list, adding the file name to the [0] element */
char	**args_to_argv(char **args, char *cmd_path)
{
	char	**argv;
	int		num;
	int		i;

	if (!cmd_path)
		return (NULL);
	i = 0;
	num = count_args(args) + 2;
	argv = (char **)malloc(sizeof(char *) * num);
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd_path);
	if (!argv[0])
		return (free(argv), NULL);
	while (args && args[i])
	{
		argv[i + 1] = ft_strdup(args[i]);
		if (argv[i + 1] == NULL)
			return (free_arr_str(argv), NULL);
		i++;
	}
	argv[i + 1] = NULL;
	return (argv);
}

/* this function makes copy of the 'src'
*  array of strings and return it	  */
char	**copy_arr_str(char **src)
{
	char	**arr_cpy;
	int		str_num;
	int		i;

	i = -1;
	str_num = count_args(src) + 1;
	arr_cpy = (char **)malloc(sizeof(char *) * str_num);
	if (!arr_cpy)
		return (NULL);
	while (src[++i])
	{
		arr_cpy[i] = ft_strdup(src[i]);
		if (!arr_cpy[i])
			return (free_arr_str(arr_cpy), NULL);
	}
	arr_cpy[i] = NULL;
	return (arr_cpy);
}

void	close_all_pipes(int **pipes, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}
