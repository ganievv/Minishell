/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:42:25 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/09 18:22:48 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pipe_after_pipe(t_token *head)
{
	return (head->type == 2 && (!(head->next) || head->next->type == 2));
}

static int	redir_and_after_not_word(t_token *head)
{
	return ((head->type == 4 || head->type == 3
			|| head->type == 6
			|| head->type == 5)
		&& (head->next && head->next->type != 0));
}

void	check_syntax_errors(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (pipe_after_pipe(current))
		{
			ft_putstr_fd("Syntax error:  consecutive "
				"pipes or pipe at the end\n", 52);
			token_free(head);
			exit(1);
		}
		if (redir_and_after_not_word(current))
		{
			ft_putstr_fd("Syntax error:  invalid redirections\n", 36);
			token_free(head);
			exit(1);
		}
		current = current->next;
	}
}
