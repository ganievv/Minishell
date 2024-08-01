/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/01 17:12:02 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipe_error_start(char *input)
{
	if (input[0] == '|')
	{
		ft_putstr_fd("The prompt must no start with '|'", 2);
		exit(1);
	}
}

void	pipe_error_end(char *input, t_token **head)
{
	t_token	*temp;

	temp = (*head);
	while (temp->next)
		temp = temp->next;
	if (temp->type == PIPE)
	{
		ft_putstr_fd("Syntax Error: The prompt should not end with a pipe", 2);
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