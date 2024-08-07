/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/07 16:22:35 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// error for pipes

void	pipe_error_start(char *input)
{
	if (input[0] == '|')
	{
		ft_putstr_fd("The prompt must not start with '|'\n", 2);
		exit(1);
	}
}

void	pipe_error_end(t_token **head)
{
	t_token	*temp;

	temp = (*head);
	while (temp->next)
		temp = temp->next;
	if (temp->type == PIPE)
	{
		ft_putstr_fd("Syntax Error: The prompt should not end with '|'\n", 2);
		token_free(head);
		exit(1);
	}
}

void	token_free(t_token **head)
{
	t_token	*current;
	t_token	*next_token;

	current = (*head);
	next_token = NULL;
	while (current)
	{
		next_token = current->next;
		free(current);
		current = next_token;
	}
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;

	while (current)
	{
		printf("Token: %.*s, Type: %d\n", current->len,
			current->token_start, current->type);
		current = current->next;
	}
}
