/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_main_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:58:50 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/18 15:42:59 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	t_msh_init(t_msh *info, char **envp)
{
	info->input = NULL;
	info->tokens = NULL;
	info->cmds = NULL;
	info->pids = NULL;
	info->pipes = NULL;
	info->last_exit_status = 0;
	info->envp = copy_arr_str(envp);
	init_builtin_names(info->builtin_names);
	init_builtin_ptrs(info->builtin_ptrs);
}

// clear screen before prompt
void	clear_screen(void)
{
	printf("\033[H\033[J");
}

int	is_input_empty(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (0);
		input++;
	}
	return (1);
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
void	init_builtin_ptrs(int (**builtin_ptrs)(char **, char ***, t_msh *))
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
