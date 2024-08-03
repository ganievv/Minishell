/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/03 19:07:00 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//a function that is giving you back what type of enum is the string

void	token_h_sep(char *input, t_token **head, t_h_token *var)
{
	var->len = 1;
	if ((input[var->i] == '>' && input[var->i + 1] == '>')
		|| (input[var->i] == '<' && input[var->i + 1] == '<'))
		var->len = 2;
	token_lstadd(head, token_create(input + (var->start), var->len,
			token_type(input + (var->start), var->len)));
	var->i += var->len;
}

void	token_h_quote(char *input, t_token **head, t_h_token *var)
{
	char	q_type;

	q_type = input[var->i];
	var->start = var->i;
	(var->i)++;
	while (input[(var->i)] && input[var->i] != q_type)
		(var->i)++;
	if (input[var->i] == q_type)
	{
		var->len = var->i - var->start + 1;
		token_lstadd(head, token_create(input + (var->start), var->len,
				(q_type == '\'') * S_QUOTED + (q_type == '\"') * D_QUOTED));
		(var->i)++;
	}
	else
	{
		ft_putstr_fd("Error: Unmatched or Unterminated quotes\n", 2);
		exit(1);
	}
}

void	token_h_word(char *input, t_token **head, t_h_token *var)
{
	while (input[var->i] && !ft_isspace(input[var->i])
		&& !is_seperator(input[var->i]))
		(var->i)++;
	var->len = var->i - var->start;
	token_lstadd(head, token_create(input + (var->start), var->len,
			token_type(input + (var->start), var->len)));
}

void	token_h_variable(char *input, t_token **head, t_h_token *var)
{
	(var->i)++;
	var->start = var->i;
	if (input[var->i] == '?' || ft_isdigit(input[var->i]))
		(var->i)++;
	else
		while (input[var->i] && (ft_isalnum(input[var->i])
				|| input[var->i] == '_'))
			(var->i)++ ;
	var->len = var->i - var->start;
	token_lstadd(head, token_create(input + (var->start) - 1,
			var->len + 1, EXP_FIELD));
}

void	tokenize(char *input, t_token **head)
{
	t_h_token	var;

	var.i = 0;
	var.len = 0;
	pipe_error_start(input);
	while (input[var.i] != '\0')
	{
		while (input[var.i] && ft_isspace(input[var.i]))
			var.i++;
		if (input[var.i] == '\0')
			return ;
		var.start = var.i;
		if (is_seperator(input[var.i]))
			token_h_sep(input, head, &var);
		else if (is_quote(input[var.i]))
			token_h_quote(input, head, &var);
		else if (input[var.i] == '$')
			token_h_variable(input, head, &var);
		else
			token_h_word(input, head, &var);
	}
	pipe_error_end(head);
}

// int main() {
//     char *input = "echo Hello | cd $HOME";
//     t_token *head = NULL;

//     tokenize(input, &head);
//     print_tokens(head);

//     // Free the tokens
//     t_token *current = head;
//     while (current)
// 	{
//         t_token *next = current->next;
//         free(current);
//         current = next;
//     }
//     return (0);
// }