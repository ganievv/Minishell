/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:03:55 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/26 15:07:27 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function checks if a given command is a builtin;
*
*  return values:
*				  '-1'   -> not a builtin cmd
*				  '>= 0' -> a builtin cmd			  */
int	is_cmd_builtin(char *cmd, t_msh *info)
{
	int	i;

	i = 0;
	while (info->builtin_names[i] != NULL)
	{
		if (strcmp(cmd, info->builtin_names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* this function counts how many
*  strings a given array has  */
int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/* this function counts how many
*  nodes a given linked list has */
int	count_cmds(t_pipe_group *cmds)
{
	int	count;

	count = 0;
	while (cmds != NULL)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

/* this function initializes an array of builtin names */
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

/* this function initializes an array of pointers to builtin functions */
void	init_builtin_ptrs(int (**builtin_ptrs)(char **, t_env_vars **))
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
