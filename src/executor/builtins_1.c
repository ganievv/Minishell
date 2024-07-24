/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/23 13:14:52 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* for pwd, cd commands:
*  should we use -l c option to qcc when we compile the project ??? */

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

/* We should skip all flags in the parser or lexer,
*  because of this sentence in the subject:
*  'cd with only a relative or absolute path'
*
*  We should change PWD env var in 'ft_cd()' */

int	ft_cd(char **args)
{
	char	*dir;

	if (!args[0])
	{
		dir = getenv("HOME");
		if (!dir)
			return (1);
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

/* '-n' flag should be in args[0] */

int	ft_echo(char **args)
{
	bool	put_new_line;

	put_new_line = true;
	if (*args && (ft_strcmp("-n", *args) == 0))
	{
		put_new_line = false;
		args++;
	}
	while (*args)
	{
		write (STDOUT_FILENO, *args++, ft_strlen(*args));
		if (*args)
			write (STDOUT_FILENO, " ", 1);
	}
	if (put_new_line)
		write (STDOUT_FILENO, "\n", 1);
	return (0);
}

/* we should do it in executor.c:
*  if (args[0] == NULL) ->  args[0] = $?*/

int	ft_exit(char **args)
{
	long long	n_nbr;

	/* in this case it will not exit*/
	if (count_args(args) >= 2)
	{
		write (STDERR_FILENO, "msh: exit: too many arguments", 29);
		return (1);
	}
	if (!is_nbr(*args) || !is_valid_range(*args))
	{
		write (STDERR_FILENO, "msh: exit: numeric argument required", 36);
		exit(1);
	}
	n_nbr = ft_atoll(*args);
	exit(n_nbr % 256);
}
