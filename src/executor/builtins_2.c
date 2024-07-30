/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 15:44:55 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* I am assuming that we have skipped all flags
*  in lexer or parser step*/

int	ft_export(char **args, char **envp)
{
	if (!*args)
		print_env_vars();
	else
	{
		while (*args)
		{
			if (!is_export_arg_valid(*args))
				return (1);
			//create_node(*args, env_vars);
			args++;
		}
	}
	return (0);
}

int	ft_unset(char **args, t_env_vars **env_vars)
{
	if (!*args)
		return (0);
	while (*args)
	{
		remove_env_var(env_vars, *args);
		args++;
	}
}

int	ft_env(char **args, t_env_vars **env_vars)
{
	t_env_vars	*cur;

	cur = *env_vars;
	while (cur)
	{
		write (STDOUT_FILENO, cur->var, ft_strlen(cur->var));
		write (STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (0);
}
