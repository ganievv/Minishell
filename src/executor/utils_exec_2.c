/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:42:29 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/24 20:55:02 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_builtin_names(char **builtin_names)
{
	builtin_names[0] = "echo";
	builtin_names[1] = "cd";
	builtin_names[2] = "pwd";
	builtin_names[3] = "export";
	builtin_names[4] = "unset";
	builtin_names[5] = "env";
	builtin_names[6] = "exit";
	builtin_names[7] = NULL;
}

void	init_builtin_ptrs(int (**builtin_ptrs)(char **))
{
	builtin_ptrs[0] = ft_echo;
	builtin_ptrs[1] = ft_cd;
	builtin_ptrs[2] = ft_pwd;
	builtin_ptrs[3] = ft_export;
	builtin_ptrs[4] = ft_unset;
	builtin_ptrs[5] = ft_env;
	builtin_ptrs[6] = ft_exit;
	builtin_ptrs[7] = NULL;
}

static void	print_err_for_export(char *arg)
{
	write(STDERR_FILENO, "msh: export: `", 14);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier", 25);
}

int	is_export_arg_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && (arg[i] != '_'))
		return (print_err_for_export(arg), 0);
	i++;
	while ((arg[i] != '=') && arg[i])
	{
		if (!ft_isalnum(arg[i]) && (arg[i] != '_'))
			return (print_err_for_export(arg), 0);
		i++;
	}
	return (1);
}
