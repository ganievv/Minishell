/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exec_file_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:31:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/06 21:04:07 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function makes a copy of the directory path where the 'is_file_present()'
*  function found an executable file; frees the array of strings 'path_arr';
*  and closes the directory stream referred to by the parameter 'dir'			*/
static void	clean_and_copy(DIR *dir, char **path_arr, int i, char **e_dir)
{
	*e_dir = ft_strdup(path_arr[i]);
	free_arr_str(path_arr);
	closedir(dir);
}

/* this function checks if 'file' is present
*  in the 'dir' directory;
*
*  return values:
*				  [file_ptr] -> if 'file' is present
*				  NULL       ->	if 'file' is not present */
static char	*is_file_present(DIR *dir, char *file)
{
	struct dirent	*entry;
	char			*file_cp;

	file_cp = str_to_lower_case(file);
	while (true)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strcmp(entry->d_name, file) == 0)
			return (file);
		if (file_cp && ft_strcmp(entry->d_name, file_cp) == 0)
		{
			
		}
	}
	return (NULL);
}

/* this function searches for the executable 'file' in directories
*  listed in the 'PATH' environment;
*
*  return values:
*				  NULL  ->  if an error occurs or if 'file' is
*							not found in any directory;
*				  [dir]	->  path to the directory containing the
*							executable file (allocated with malloc()) */
char	*search_exec_dir(char *file, char *path_env_v)
{
	DIR				*dir;
	char			**path_arr;
	char			*e_dir;
	int				i;

	if (ft_strchr(info->envp[cmd_i], '=') + 1)
		;
	if (*path_env_v == '\0')
		return (NULL);
	path_arr = ft_split(path_env_v, ':');
	if (!path_arr)
		return (NULL);
	i = -1;
	e_dir = NULL;
	while (path_arr[++i])
	{
		dir = opendir(path_arr[i]);
		if (dir)
		{
			if (is_file_present(dir, file))
				return (clean_and_copy(dir, path_arr, i, &e_dir), e_dir);
			closedir(dir);
		}
	}
	return (free_arr_str(path_arr), e_dir);
}
