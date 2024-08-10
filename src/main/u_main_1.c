/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_main_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:58:50 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/10 20:26:05 by sganiev          ###   ########.fr       */
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

void	free_all_prog_vars(t_msh *info)
{
	pipe_group_free(&(info->cmds));
	token_free(&(info->tokens));
	if (info->input)
	{
		free(info->input);
		info->input = NULL;
	}
	free_pids_and_pipes(info);
}
