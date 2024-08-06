/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/06 16:39:35 by sganiev          ###   ########.fr       */
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
		perror("msh: pwd: error getting current directory");
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
	if (!args || !args[0])
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
		perror("msh: cd: error changing directory");
		write(STDOUT_FILENO, "\n", 1);
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
	if (args && *args && (ft_strcmp("-n", *args) == 0))
	{
		put_new_line = false;
		args++;
	}
	while (args && *args)
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
	char		*exit_arg;

	(void)envp;
	if (!args || !args[0])
		exit_arg = ft_itoa(info->last_exit_status);
	else
		exit_arg = args[0];
	if (!is_nbr(exit_arg) || !is_valid_exit_range(exit_arg))
	{
		write (STDERR_FILENO, "msh: exit: numeric argument required", 36);
		write(STDOUT_FILENO, "\n", 1);
		//free_all_prog_vars(info);
		exit(1);
	}
	if (args && (count_args(args) >= 2))
	{
		write (STDERR_FILENO, "msh: exit: too many arguments", 29);
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	n_nbr = ft_atoll(exit_arg);
	//free_all_prog_vars(info);
	exit(n_nbr % 256);
}
