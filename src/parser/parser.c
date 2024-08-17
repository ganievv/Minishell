/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:28:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/17 00:46:05 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_group_list(t_pipe_group **head,
			t_pipe_group **current, t_pipe_group *group, t_token **tokens)
{
	if (!(*head))
	{
		(*head) = group;
		(*current) = (*head);
	}
	else
	{
		(*current)->next = group;
		(*current) = (*current)->next;
	}
	if (*tokens && (*tokens)->type == 2)
		*tokens = (*tokens)->next;
}

t_pipe_group	*parse_pipeline(t_rdr_const rdr, t_token **tokens)
{
	t_pipe_group	*head;
	t_pipe_group	*current;
	t_pipe_group	*group;
	t_token			*token_start;

	head = NULL;
	current = NULL;
	token_start = NULL;
	while (*tokens)
	{
		token_start = *tokens;
		group = pipe_group_init();
		while (*tokens && (*tokens)->type == SPC)
			(*tokens) = (*tokens)->next;
		parse_command(tokens, group);
		parse_args(&(*tokens), group);
		parse_redir(rdr, &token_start, group);
		update_group_list(&head, &current, group, tokens);
	}
	return (head);
}

int	p_command_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == WORD || tokens->type == EXP_FIELD
			|| tokens->type == D_QUOTED || tokens->type == S_QUOTED));
}
