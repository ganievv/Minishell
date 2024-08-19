/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_main_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 05:34:14 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 22:50:59 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_input(t_msh *info, t_rdr_const rdr)
{
	t_token	*ready;

	ready = NULL;
	if (tokenize(info->input, &(info->tokens)) != -1)
	{
		token_to_token_preexp(info->tokens, &ready);
		token_preexp_to_token_exp(info->last_exit_status, &ready, info->envp);
		free(info->input);
		token_preexp_and_update_input(&(info->input), ready);
		token_preexp_free(&ready);
		token_free(&(info->tokens));
		if (tokenize(info->input, &(info->tokens)) != -1)
			process_pipeline(info, rdr, &ready);
		free(info->input);
	}
	else
		token_free(&(info->tokens));
	if (ready != NULL)
		token_preexp_free(&(ready));
}

void	process_pipeline(t_msh *info, t_rdr_const rdr, t_token **ready)
{
	token_ready_for_parsing(info->last_exit_status,
		&(info->tokens), ready, info->envp);
	if (info->cmds)
		pipe_group_free(&(info->cmds));
	if (info->tokens)
		token_free(&(info->tokens));
	info->tokens = *ready;
	info->cmds = parse_pipeline(rdr, &(info->tokens));
	exec_all_cmds(info);
	if (info->cmds)
		pipe_group_free(&(info->cmds));
}
