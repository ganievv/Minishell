/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:20:35 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/13 15:40:41 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_word_sq_dq(char c)
{
	return (c == '$' || c == '|'
		|| c == '>' || c == '<'
		|| isspace(c));
}

int	token_is_command(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp && temp->next)
		temp = temp->next;
	return (temp == NULL || (temp->type == 2));
}

int	is_q_terminated(char *str, int start, int end)
{
	int	dq;
	int	sq;
	int	i;

	i = -1 + start;
	sq = 0;
	dq = 0;
	while (str[++i] && i < end)
	{
		if (str[i] == '\'')
			sq++;
		if (str[i] == '\"')
			dq++;
	}
	return (dq % 2 == 0 && sq % 2 == 0);
}

void	tokenize_command(char *input, t_token **head, t_h_token	*var)
{
	var->start = var->i;
	while (input[var->i] && !is_word_sq_dq(input[var->i]))
		(var->i++);
	//printf("%d\n", var->i);
	if (!is_q_terminated(input, var->start, var->i))
	{
		ft_putstr_fd("Syntax Error: Unterminated quotes\n", 2);
		free(input);
		input = NULL;
		token_free(head);
		exit(1);
	}
	var->len = var->i - var->start;
	token_lstadd(head, token_create(input + (var->start), var->len,
			WORD));
}
