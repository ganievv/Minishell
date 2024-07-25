/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/25 16:04:24 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* I am assuming that we have skipped all flags
*  in lexer or parser step*/

int	ft_export(char **args, t_env_vars **env_vars)
{
	t_env_vars *curr;

	curr = *env_vars;
	if (!*args)
	{
		while (curr)
		{
			write (STDOUT_FILENO, "declare -x ", 11);
			write (STDOUT_FILENO, curr->var, ft_strlen(curr->var));
			write (STDOUT_FILENO, "\n", 1);
			curr = curr->next;
		}
	}
	else
	{
		while (*args)
		{
			if (!is_export_arg_valid(*args))
				return (1);
			create_node(*args, env_vars);
			args++;
		}
	}
	return (0);
}

int	ft_unset(char **args, t_env_vars **env_vars)
{
}

int	ft_env(char **args, t_env_vars **env_vars)
{
}
