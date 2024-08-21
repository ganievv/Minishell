/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:28:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 07:37:15 by tnakas           ###   ########.fr       */
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
	t_token			*tmp;

	head = NULL;
	current = NULL;
	token_start = NULL;
	group = NULL;
	tmp = *tokens;
	while (tmp)
	{
		token_start = tmp;
		group = pipe_group_init();
		while (tmp && tmp->type == SPC)
			tmp = tmp->next;
		parse_command(&tmp, group);
		parse_args(&tmp, group);
		parse_redir(rdr, &token_start, group);
		update_group_list(&head, &current, group, &tmp);
	}
	return (head);
}

int	p_command_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == WORD || tokens->type == EXP_FIELD
			|| tokens->type == D_QUOTED || tokens->type == S_QUOTED));
}
