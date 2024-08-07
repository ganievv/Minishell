/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:42:25 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/07 16:16:23 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pipe_after_pipe(t_token *head)
{
	printf("head->type == pipe || %d\n", head->type == 2);
	printf("head->next->type == pipe || %d\n", head->next->type == 2);
	return (head->type == 2 && (!(head->next) || head->next->type == 2));
}

static int	redir_and_after_not_word(t_token *head)
{
	return ((head->type == 4 || head->type == 3
			|| head->type == 6
			|| head->type == 5 || head->type == 2)
		&& (head->next || head->next->type != 0));
}

void	check_syntax_errors(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		printf("type : %d\n", current->type);
		if (pipe_after_pipe(current))
		{
			ft_putstr_fd("Syntax error:  consecutive pipes\n", 2);
			token_free(head);
			exit(1);
		}
		if (redir_and_after_not_word(current))
		{
			ft_putstr_fd("Syntax error:  invalid redirections\n", 2);
			token_free(head);
			exit(1);
		}
		current = current->next;
	}
}
