/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/18 15:42:55 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	syntax_tests(t_token **head, int i)
{
	if (i == -1)
		return (-1);
	else if (check_syntax_errors(head) == -1
		|| pipe_error_end(head) == -1)
		return (-1);
	return (0);
}

int	tokenize(char *input, t_token **head)
{
	t_h_token	var;

	var.i = 0;
	var.len = 0;
	while (input[var.i])
	{
		if (input[var.i] == '\0')
			return (0);
		var.start = var.i;
		if (input[var.start] && ft_isspace(input[var.start]))
			token_h_isspace(input, head, &var);
		else if (is_seperator(input[var.i]))
			token_h_sep(input, head, &var);
		else if (is_quote(input[var.i]))
		{
			if (token_h_quote(input, head, &var) == -1)
				break ;
		}
		else if (input[var.i] == '$')
			token_h_variable(input, head, &var);
		else
			token_h_word(input, head, &var);
	}
	return (syntax_tests(head, var.i));
}
