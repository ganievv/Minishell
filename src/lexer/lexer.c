/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/13 21:24:44 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tokenize(char *input, t_token **head)
{
	t_h_token	var;

	var.i = 0;
	var.len = 0;
	pipe_error_start(input);
	while (input[var.i])
	{
		if (input[var.i] == '\0')
			return ;
		var.start = var.i;
		if (input[var.start] && ft_isspace(input[var.start]))
			token_h_isspace(input, head, &var);
		else if (token_is_command(*head))
			tokenize_command(input, head, &var);
		else if (is_seperator(input[var.i]))
			token_h_sep(input, head, &var);
		else if (is_quote(input[var.i]))
			token_h_quote(input, head, &var);
		else if (input[var.i] == '$')
			token_h_variable(input, head, &var);
		else
			token_h_word(input, head, &var);
	}
	pipe_error_end(head);
	check_syntax_errors(head);
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