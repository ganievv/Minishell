/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:44 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/23 17:26:17 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_builtin_names(char **builtin_names)
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

static void	init_builtin_ptrs(int (**builtin_ptrs)(char **))
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

static int	exec_external_cmd(t_pipe_group *group)
{
}

static int	exec_one_cmd(t_pipe_group *group, char **builtin_names,
	int (**builtin_ptrs)(char **))
{
	int	i;

	i = 0;
	while (builtin_ptrs[i] != NULL)
	{
		if (strcmp(group->command, builtin_names[i]) == 0)
			return (*builtin_ptrs[i])(group->args);
		i++;
	}

	return (exec_external_cmd(group));
}

int	exec_all_cmds(t_msh *info)
{
	char	*builtin_names[BUILTIN_NUM + 1];
	int		(*builtin_ptrs[BUILTIN_NUM + 1]) (char **args);

	init_builtin_names(builtin_names);
	init_builtin_ptrs(builtin_ptrs);
	if (count_groups(groups) == 1)
		exec_one_cmd(groups, builtin_names, builtin_ptrs, envp);
	else
	{
		while (groups != NULL)
		{
			groups = groups->next;
		}
	}
}
