/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/02 20:50:26 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function marks each argument of the 'export' cmd
*  to be passed to child processes in the environment;
*
*  return values:
*				  0 -> if each arg was valid
*				  1 -> if one or more args were not valid */
int	ft_export(char **args, char ***envp, t_msh *info)
{
	int	estatus;

	estatus = 0;
	args = skip_all_flags(args);
	if (!*args)
		print_env_vars(*envp);
	else
	{
		while (*args)
		{
			if (is_export_arg_valid(*args))
				change_or_add_env_var(*args, envp);
			else
				estatus = 1;
			args++;
		}
	}
	return (estatus);
}

int	ft_unset(char **args, char ***envp, t_msh *info)
{
	args = skip_all_flags(args);
	if (!args)
		return (0);
	while (*args)
	{
		remove_env_var(*args, envp);
		args++;
	}
	return (0);
}

int	ft_env(char **args, char ***envp, t_msh *info)
{
	char	**cur;

	args = NULL;
	if (!envp || !*envp)
		return (0);
	cur = *envp;
	while (*cur)
	{
		write (STDOUT_FILENO, *cur, ft_strlen(*cur));
		write (STDOUT_FILENO, "\n", 1);
		cur++;
	}
	return (0);
}
