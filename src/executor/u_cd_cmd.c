/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cd_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:06:01 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/12 19:40:02 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd_var(char ***envp)
{
	char	buff[PATH_MAX];
	char	*buff_ptr;
	int		var_i;
	char	*new_path;

	buff_ptr = getcwd(buff, sizeof(buff));
	if (buff_ptr)
	{
		new_path = ft_strjoin("PWD=", buff);
		if (!new_path)
			return ;
		var_i = search_env_var("PWD", *envp);
		if (var_i != -1)
		{
			free((*envp)[var_i]);
			(*envp)[var_i] = new_path;
		}
		else
			free_str(&new_path);
	}
}

void	update_oldpwd_var(char ***envp)
{
	char	*pwd_value;
	char	*oldpwd;
	int		pwd_i;

	pwd_value = NULL;
	oldpwd = NULL;
	pwd_i = search_env_var("PWD", *envp);
	if (pwd_i == -1)
		return ;
	else
		pwd_value = take_env_var_value((*envp)[pwd_i]);
	if (pwd_value)
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd_value);
		free_str(&pwd_value);
		if (!oldpwd)
			return ;
		change_or_add_env_var(oldpwd, envp);
		free_str(&oldpwd);
	}
}

static char	*search_oldpwd(char *to_search, char **envp)
{
	char	*dir;
	int		index;

	dir = NULL;
	index = search_env_var(to_search, envp);
	if (index != -1)
		dir = take_env_var_value(envp[index]);
	return (dir);
}

int	check_special_cd_options(char **dir, char **envp)
{
	char	*new_dir;

	if (!dir || !*dir)
		return (0);
	if (ft_strcmp("-", *dir) == 0)
	{
		new_dir = search_oldpwd("OLDPWD", envp);
		if (!new_dir)
			return (write(STDERR_FILENO, "cd: OLDPWD not set\n", 19), 0);
		free_str(dir);
		*dir = new_dir;
	}
	return (1);
}

void	print_err_for_cd(char *dir)
{
	write(STDERR_FILENO, "msh: cd: ", 9);
	write(STDERR_FILENO, dir, ft_strlen(dir));
	write(STDERR_FILENO, ": ", 2);
	perror("");
}
