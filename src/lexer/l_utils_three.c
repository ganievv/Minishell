/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/20 19:05:28 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// error for pipes

void	pipe_error_start(char *input)
{
	int	i;

	i = -1;
	while (ft_isspace(input[++i]))
		;
	if (input[i] == '|' )
	{
		ft_putstr_fd("The prompt must not start with '|'\n", 2);
		exit(1);
	}
}

int	pipe_error_end(t_token **head)
{
	t_token	*temp;

	if (!head || !*head)
		return (0);
	temp = (*head);
	while (temp->next)
		temp = temp->next;
	if (temp->type == PIPE)
	{
		ft_putstr_fd("Syntax Error: The prompt should not end with '|'\n", 2);
		return (-1);
	}
	return (0);
}

void	token_free(t_token **head)
{
	t_token	*current;
	t_token	*next_token;

	if (!head || !*head)
		return ;
	current = (*head);
	next_token = NULL;
	while (current)
	{
		next_token = current->next;
		free(current);
		current = next_token;
	}
	*head = NULL;
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("Token: %s, len= %d, Type: %d\n",
			current->token_start, current->len, current->type);
		current = current->next;
	}
}
