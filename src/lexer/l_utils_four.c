/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:42:25 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 02:20:44 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	pipe_after_pipe(t_token *head)
{
	t_token	*c_tok;
	t_token	*temp;
	int		cont1;

	c_tok = head;
	temp = NULL;
	if (c_tok && c_tok->next)
		temp = c_tok->next;
	while (temp && temp->type == SPC)
		temp = temp->next;
	cont1 = (c_tok && (c_tok->type >= 2 && c_tok->type <= 6) && (!temp
				|| (temp && (temp->type >= 2 && temp->type <= 6))));
	return (cont1);
}

// static int	redir_and_after_not_word(t_token *head)
// {
// 	t_token	*c_tok;
// 	t_token	*temp;

// 	c_tok = head;
// 	temp = NULL;
// 	if (c_tok && c_tok->next)
// 		temp = c_tok->next;
// 	while (temp && temp->type == SPC)
// 		temp = temp->next;
// 	return ((c_tok->type == 4 || c_tok->type == 3 || c_tok->type == 6
// 			|| c_tok->type == 5) && ((temp && (temp->type != 0)) || (!temp)));
// }

static int	ft_token_print_error(t_token **head, char *message)
{
	ft_putstr_fd(message, 2);
	token_free(head);
	return (-1);
}

int	check_syntax_errors(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current && current->type == SPC)
		current = current->next;
	if (current && (current->type == PIPE))
		return (ft_token_print_error(head,
				"msh:  unexpected token\n"));
	while (current)
	{
		if (pipe_after_pipe(current))
			return (ft_token_print_error(head, "msh: syntax error near"
					" unexpected token\n"));
		current = current->next;
	}
	return (0);
}
