/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:47:27 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/03 13:27:36 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	parse_redir_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == REDIR_IN
			|| tokens->type == REDIR_OUT
			|| tokens->type == APPEND_DELIMITER
			|| tokens->type == DELIMITER));
}

static void	parse_redir_h_two(t_token_type type,
			t_pipe_group **group, char *file)
{
	if (type == 3 || type == 6)
	{
		(*group)->file_in = file;
		(*group)->redir_out = 1;
		(*group)->mode_out = (type == 6) * O_APPEND
			+ (type == 3) * O_TRUNC;
	}
	else
	{
		(*group)->file_in = file;
		(*group)->redir_in = 1;
		(*group)->mode_in = O_RDONLY;
	}
}

void	parse_redir(t_token **tokens, t_pipe_group *group)
{
	t_token_type	type;
	t_token			*temp;
	char			*file;

	type = -1;
	temp = *tokens;
	file = NULL;
	while (parse_redir_h(temp))
	{
		type = temp->type;
		tokens = temp->next;
		if (temp && temp->type == WORD)
		{
			file = token_content_extract(temp);
			parse_redir_h_two(type, &group, file);
			temp = temp->next;
		}
	}
}
