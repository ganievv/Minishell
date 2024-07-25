/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:31:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/25 23:04:47 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function checks if a given command is a builtin;
*
*  return values:
*				  '-1'   -> not a builtin cmd
*				  '>= 0' -> a builtin cmd			  */
int	is_cmd_builtin(char *cmd, t_msh *info)
{
	int	i;

	i = 0;
	while (info->builtin_names[i] != NULL)
	{
		if (strcmp(cmd, info->builtin_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*is_file_present(DIR *dir, char *file)
{
	struct dirent	*dir_inf;

	dir_inf = readdir(dir);
	while (dir_inf)
	{
		if (ft_strcmp(dir_inf->d_name, file) == 0)
			return (dir_inf->d_name);
		dir_inf = readdir(dir);
	}
	return (NULL);
}

/* ??? does ft_split() split 'str' if there is no delimeters ???*/
char	*search_exec_dir(char *file, char *path_env_v)
{
	char			**path_arr;
	int				i;
	DIR				*dir;

	if (*path_env_v == '\0')
		return (NULL);
	path_arr = ft_split(path_env_v, ':');
	while (path_arr[i])
	{
		dir = opendir(path_arr[i]);
		if (!dir)
			return (NULL);
		if (is_file_present(dir, file) != NULL)
			return (path_arr[i]);
		if (closedir(dir) == -1)
			return (NULL);
	}
	return (NULL);
}
