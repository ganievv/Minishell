/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exec_file_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 20:31:52 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/07 14:50:33 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*make_absolute_path(char *dir, char *file)
{
	char	*absolute_path;
	char	*tmp;

	absolute_path = ft_strjoin(dir, "/");
	if (!absolute_path)
		return (NULL);
	tmp = absolute_path;
	absolute_path = ft_strjoin(absolute_path, file);
	free(tmp);
	return (absolute_path);
}

/* this function checks if 'file' is present
*  in the 'dir' directory;
*
*  return values:
*				  [file_ptr] -> if 'file' is present
*				  NULL       ->	if 'file' is not present */
static char	*is_file_present(DIR *dir, char *file, char **path_arr, int i)
{
	struct dirent	*entry;
	char			*lfile;
	char			*absolute_path;

	absolute_path = NULL;
	lfile = str_to_lower_case(file);
	while (true)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strcmp(entry->d_name, file) == 0)
		{
			absolute_path = make_absolute_path(path_arr[i], file);
			break ;
		}
		else if (lfile && ft_strcmp(entry->d_name, lfile) == 0)
		{
			absolute_path = make_absolute_path(path_arr[i], lfile);
			break ;
		}
	}
	if (lfile)
		free(lfile);
	return (absolute_path);
}

static char	**dirs_to_str_arr(char *path_env_v)
{
	char	**path_arr;
	char	*start;

	start = ft_strchr(path_env_v, '=');
	if (!start)
		return (NULL);
	start++;
	if (*start == '\0')
		return (NULL);
	path_arr = ft_split(start, ':');
	return (path_arr);
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

	path_arr = dirs_to_str_arr(path_env_v);
	if (!path_arr)
		return (NULL);
	i = -1;
	e_dir = NULL;
	while (path_arr[++i])
	{
		dir = opendir(path_arr[i]);
		if (dir)
		{
			e_dir = is_file_present(dir, file, path_arr, i);
			if (e_dir)
				return (free_arr_str(path_arr), closedir(dir), e_dir);
			closedir(dir);
		}
	}
	return (free_arr_str(path_arr), e_dir);
}
