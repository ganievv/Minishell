/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:42:25 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/15 18:31:37 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pipe_after_pipe(t_token *head)
{
	t_token	*current_token;
	t_token	*temp;
	t_token	*not_space_token;

	current_token = head;
	temp = NULL;
	if (current_token && current_token->next)
		temp = current_token->next;
	while (temp && temp->type == SPC)
		temp = temp->next;
	not_space_token = temp;
	return ((current_token->type != WORD
			&& current_token->type != S_QUOTED
			&& current_token->type != D_QUOTED)
		&& (!not_space_token
			|| (not_space_token->type != WORD
				&& not_space_token->type != S_QUOTED
				&& not_space_token->type != D_QUOTED)));
}

static int	redir_and_after_not_word(t_token *head)
{
	t_token	*current_token;
	t_token	*temp;
	t_token	*not_space_token;

	current_token = head;
	temp = NULL;
	if (current_token && current_token->next)
		temp = current_token->next;
	while (temp && temp->type == SPC)
		temp = temp->next;
	not_space_token = temp;
	return ((current_token->type == 4 || current_token->type == 3
			|| current_token->type == 6
			|| current_token->type == 5)
		&& ((not_space_token
				&& (not_space_token->type != 0)) || (!not_space_token)));
}

static void	ft_token_print_error(t_token **head, char *message)
{
	ft_putstr_fd(message, 2);
	token_free(head);
	exit(1);
}

void	check_syntax_errors(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current && current->type == SPC)
		current = current->next;
	if (current && (current->type == PIPE))
		ft_token_print_error(head, "Syntax error:  unexpected token\n");
	while (current && current->next)
	{
		if (pipe_after_pipe(current))
			ft_token_print_error(head, "Syntax error: consecutive "
				"non verbal tokens\n");
		if (redir_and_after_not_word(current))
			ft_token_print_error(head, "Syntax error:  \
			invalid redirections\n");
		current = current->next;
	}
}
