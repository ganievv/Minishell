/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/19 20:52:38 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// for pwd, cd commands:
// should we use -l c option to qcc when we compile the project ???

static void	pwd_errno_check(void)
{
	if (errno == EINVAL)
		write (STDERR_FILENO, "The argument size is negative or 0", 34);
	else if (errno == ELOOP)
		write (STDERR_FILENO, "Too many levels of symbolic links", 33);
	else if (errno == ENOSYS)
		write (STDERR_FILENO, "The getcwd() function isn't "
			"implemented for the filesystem specified in the "
			"current working directory", 101);
	else if (errno == ERANGE)
		write (STDERR_FILENO, "The buffer is too small (as specified "
			"by size) to contain the name of the current "
			"working directory", 99);
}

int	ft_pwd(char **args)
{
	char	buff[PATH_MAX];
	char	*buff_ptr;

	buff_ptr = getcwd(buff, sizeof(buff));
	if (!buff_ptr)
	{
		pwd_errno_check();
		return (1);
	}
	write(STDOUT_FILENO, buff_ptr, ft_strlen(buff_ptr));
	return (0);
}

static void	cd_errno_check(void)
{
	if (errno == EACCES)
		write (STDERR_FILENO, "Search permission is "
			"denied for a component of path", 51);
	else if (errno == EINTR)
		write (STDERR_FILENO, "The call was interrupted "
			"by a signal", 36);
	else if (errno == ELOOP)
		write (STDERR_FILENO, "Too many levels of "
			"symbolic links or prefixes", 45);
	else if (errno == ENAMETOOLONG)
		write (STDERR_FILENO, "The path argument is longer "
			"than PATH_MAX, or a pathname component is "
			"longer than NAME_MAX", 90);
	else if (errno == ENOENT)
		write (STDERR_FILENO, "The specified path doesn't "
			"exist, or path is an empty string.", 61);
	else if (errno == ENOMEM)
		write (STDERR_FILENO, "There wasn't enough memory to "
			"allocate a control structure.", 59);
	else if (errno == ENOSYS)
		write (STDERR_FILENO, "The chdir() function isn't implemented "
			"for the filesystem underlying the path specified in path", 95);
	else if (errno == ENOTDIR)
		write (STDERR_FILENO, "A component of path isn't a directory", 37);
}

// We should skip all flags in the parser or lexer,
// because of this sentence in the subject:
// 'cd with only a relative or absolute path'

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
		cd_errno_check();
		return (1);
	}
	return (0);
}
