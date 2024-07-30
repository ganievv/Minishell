/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/30 20:27:22 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* for pwd, cd commands:
*  should we use -l c option to qcc when we compile the project ??? */
int	ft_pwd(char **args, char ***envp)
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
int	ft_cd(char **args, char ***envp)
{
	char	*dir;
	int		home_i;

	if (!args[0])
	{
		home_i = search_env_var("HOME", *envp);
		if (home_i == -1)
			return (1);
		else
			dir = take_env_var_value(*envp[home_i]);
	}
	else
		dir = ft_strdup(args[0]);
	if (dir && chdir(dir) == -1)
	{
		perror("Error changing directory");
		return (1);
	}
	return (update_pwd_var(envp), free(dir), 0);
}

/* '-n' flag should be in args[0] */
int	ft_echo(char **args, char ***envp)
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

/* if count_args(args) >= 2 it should not exit*/
/* 'exit 5 f'; 'exit f 5'; 'exit r t' */
int	ft_exit(char **args, char ***envp)
{
	long long	n_nbr;

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
