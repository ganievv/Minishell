/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/05 17:57:03 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function is an implemenation of the 'pwd' builtin;
*  it prints the absolute pathname of the current working
*  directory;
*
*  return values:
*				  0 -> successful retrieval of current dir
*				  1 -> an error was encountered */
int	ft_pwd(char **args, char ***envp, t_msh *info)
{
	char	buff[PATH_MAX];
	char	*buff_ptr;

	(void)args;
	(void)envp;
	(void)info;
	buff_ptr = getcwd(buff, sizeof(buff));
	if (!buff_ptr)
	{
		perror("Error getting current directory");
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	write(STDOUT_FILENO, buff, ft_strlen(buff));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	ft_cd(char **args, char ***envp, t_msh *info)
{
	char	*dir;
	int		home_i;

	(void)info;
	args = skip_all_flags(args);
	if (!args[0])
	{
		home_i = search_env_var("HOME", *envp);
		if (home_i == -1)
			return (1);
		else
			dir = take_env_var_value((*envp)[home_i]);
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
int	ft_echo(char **args, char ***envp, t_msh *info)
{
	bool	put_new_line;

	(void)envp;
	(void)info;
	put_new_line = true;
	if (*args && (ft_strcmp("-n", *args) == 0))
	{
		put_new_line = false;
		args++;
	}
	while (*args)
	{
		write (STDOUT_FILENO, *args, ft_strlen(*args));
		args++;
		if (*args)
			write (STDOUT_FILENO, " ", 1);
	}
	if (put_new_line)
		write (STDOUT_FILENO, "\n", 1);
	return (0);
}

int	ft_exit(char **args, char ***envp, t_msh *info)
{
	long long	n_nbr;

	(void)envp;
	if (args[0] == NULL)
		args[0] = ft_itoa(info->last_exit_status);
	if (!is_nbr(args[0]) || !is_valid_exit_range(args[0]))
	{
		write (STDERR_FILENO, "msh: exit: numeric argument required", 36);
		//free_all_prog_vars(info);
		exit(1);
	}
	if (count_args(args) >= 2)
	{
		write (STDERR_FILENO, "msh: exit: too many arguments", 29);
		return (1);
	}
	n_nbr = ft_atoll(*args);
	//free_all_prog_vars(info);
	exit(n_nbr % 256);
}
