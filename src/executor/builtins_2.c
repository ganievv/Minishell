/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/31 19:52:16 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* if arg is not valid then return status of the
*  command should be 1 or 0 ? */
int	ft_export(char **args, char ***envp)
{
	args = skip_all_flags(args);
	if (!*args)
		print_env_vars(*envp);
	else
	{
		while (*args)
		{
			if (is_export_arg_valid(*args))
				change_or_add_env_var(*args, envp);
			args++;
		}
	}
	return (0);
}

int	ft_unset(char **args, char ***envp)
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

int	ft_env(char **args, char ***envp)
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
