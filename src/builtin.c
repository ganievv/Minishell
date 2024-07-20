/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/20 19:33:23 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// for pwd, cd commands:
// should we use -l c option to qcc when we compile the project ???

int	ft_pwd(char **args)
{
	char	buff[PATH_MAX];
	char	*buff_ptr;

	buff_ptr = getcwd(buff, sizeof(buff));
	if (!buff_ptr)
	{
		perror("Error getting current directory");
		return (1);
	}
	write(STDOUT_FILENO, buff_ptr, ft_strlen(buff_ptr));
	return (0);
}

// We should skip all flags in the parser or lexer,
// because of this sentence in the subject:
// 'cd with only a relative or absolute path'

// We should change PWD env var in 'ft_cd()'

int	ft_cd(char **args)
{
	char	*dir;

	if (!args[0])
	{
		dir = getenv("HOME");
		if (!dir)
			return (0);
	}
	else
		dir = args[0];
	if (chdir(dir) == -1)
	{
		perror("Error changing directory");
		return (1);
	}
	return (0);
}
