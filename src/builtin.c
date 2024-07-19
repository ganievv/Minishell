/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/19 19:45:23 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(char **args)
{
	char	buff[PATH_MAX];
	char	*buff_ptr;

	buff_ptr = getcwd(buff, sizeof(buff));
	if (!buff_ptr)
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
		return (1);
	}
	return (0);
}
