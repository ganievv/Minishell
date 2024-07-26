/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exec_file_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:31:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/26 15:05:13 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
