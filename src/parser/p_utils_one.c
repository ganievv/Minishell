/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:47:27 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/17 00:42:39 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	p_redir_h_one(t_token *tokens)
{
	return (
		(tokens->type == REDIR_IN
			|| tokens->type == REDIR_OUT
			|| tokens->type == APPEND_DELIMITER
			|| tokens->type == HEREDOC));
}

void	p_redir_h_two(t_rdr_const rdr, t_token_type type,
			t_pipe_group **group, char *file)
{
	if (type == 3 || type == 6)
	{
		(*group)->file_out = file;
		(*group)->redir_out = STDOUT_FILENO;
		(*group)->mode_out = O_CREAT | O_WRONLY
			| (type == 6) * O_APPEND
			| (type == 3) * O_TRUNC;
		create_file((*group)->file_out, (*group)->mode_out);
	}
	else
	{
		if (type == HEREDOC)
		{
			(*group)->is_heredoc_in = handle_heredoc(rdr.l, file,
					(*group)->heredoc_p, rdr.envp);
			return ;
		}
		(*group)->file_in = file;
		(*group)->redir_in = STDIN_FILENO;
		(*group)->mode_in = O_RDONLY;
		close_read_end(*group);
	}
}

void	p_redir_h_three(t_token **temp, t_token **redir)
{
	*redir = (*temp);
	(*temp) = (*temp)->next;
	while ((*temp) && (*temp)->type == SPC)
		(*temp) = (*temp)->next;
}

void	p_redir_h_four(t_token **temp)
{
	if ((*temp))
		(*temp) = (*temp)->next;
	while ((*temp) && !p_redir_h_one((*temp)) && (*temp)->type != PIPE)
		(*temp) = (*temp)->next;
}

void	parse_redir(t_rdr_const rdr, t_token **tokens, t_pipe_group *group)
{
	t_token	*temp;
	t_token	*redir;

	temp = *tokens;
	while (temp && (!p_redir_h_one(temp)) && temp->type != PIPE)
		temp = temp->next;
	if (temp && temp->type == PIPE)
	{
		*tokens = temp;
		return ;
	}
	while (temp && p_redir_h_one(temp))
	{
		if (temp->type == PIPE)
			break ;
		p_redir_h_three(&temp, &redir);
		if (p_command_h_one(temp))
			p_redir_h_two(rdr, redir->type, &group, temp->token_start);
		p_redir_h_four(&temp);
	}
	*tokens = temp;
}
