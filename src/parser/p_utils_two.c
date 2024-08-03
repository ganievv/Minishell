/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:46:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/03 20:02:03 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	p_command_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == WORD || tokens->type == EXP_FIELD
			|| tokens->type == D_QUOTED || tokens->type == S_QUOTED));
}

void	parse_command(t_token **tokens, t_pipe_group *group)
{
	char	**args;
	int		arg_count;

	args = NULL;
	arg_count = 0;
	if (p_command_h_one(*tokens))
	{
		group->command = token_content_extract(*tokens);
		*tokens = (*tokens)->next;
	}
	while (p_command_h_one(*tokens))
	{
		args = ft_realloc(args, sizeof(char *) * (arg_count),
				sizeof(char *) * (arg_count + 2));
		if (!args)
			exit(1);
		args[arg_count] = token_content_extract(*tokens);
		if (!args[arg_count])
			exit(1);
		args[arg_count + 1] = NULL;
		arg_count++;
		*tokens = (*tokens)->next;
	}
	group->args = args;
}
