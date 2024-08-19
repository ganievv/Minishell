/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 21:39:10 by tnakas           ###   ########.fr       */
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
			return (write(STDERR_FILENO, "cd: HOME not set\n", 17), 1);
		dir = take_env_var_value((*envp)[home_i]);
	}
	else
		dir = ft_strdup(args[0]);
	if (!check_special_cd_options(&dir, *envp))
		return (1);
	if (dir[0] != '\0' && (chdir(dir) == -1))
		return (print_err_for_cd(dir), 1);
	update_oldpwd_var(envp);
	update_pwd_var(envp);
	return (free(dir), 0);
}

/* '-n' flag should be in args[0] */
int	ft_echo(char **args, char ***envp, t_msh *info)
{
	bool	put_new_line;

	(void)envp;
	(void)info;
	put_new_line = true;
	if (check_cmd_flag('n', &args))
		put_new_line = false;
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
		write (STDERR_FILENO, "msh: exit: numeric argument required\n", 37);
		prepare_exit(info);
		exit(255);
	}
	if (args && (count_args(args) >= 2))
	{
		write (STDERR_FILENO, "msh: exit: too many arguments\n", 30);
		return (1);
	}
	n_nbr = ft_atoll(exit_arg);
	prepare_exit(info);
	exit(n_nbr % 256);
}
