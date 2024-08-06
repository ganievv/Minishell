/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:42:25 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/06 21:55:14 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pipe_after_pipe(t_token *head)
{
	return (head->type == PIPE && head->next && head->next->type == PIPE);
}

static int	redir_and_after_not_word(t_token *head)
{
	return ((head->type == REDIR_IN || head->type == REDIR_OUT
			|| head->type == APPEND_DELIMITER
			|| head->type == DELIMITER || head->type == PIPE)
		&& (head->next || head->next->type != WORD));
}

void	check_syntax_errors(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (pipe_after_pipe(*head))
		{
			ft_putstr_fd("Syntax error:  consecutive pipes\n", 2);
			token_free(head);
			exit(1);
		}
		if (redir_and_after_not_word(*head))
		{
			ft_putstr_fd("Syntax error:  invalid redirections\n", 2);
			token_free(head);
			exit(1);
		}
		current = current->next;
	}
}
