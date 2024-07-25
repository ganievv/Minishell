/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/25 15:03:00 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* I am assuming that we have skipped all flags
*  in lexer or parser step*/

int	ft_export(char **args, char **envp)
{
	int	i;

	i = 0;
	if (!args[i])
	{
	}
	else
	{
		while (args[i])
		{
			if (!is_export_arg_valid(args[i]))
				return (1);
			i++;
		}
	}
}

int	ft_unset(char **args, char **envp)
{
}

int	ft_env(char **args, char **envp)
{
}
