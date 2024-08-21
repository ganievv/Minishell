/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:47:27 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/21 15:57:54 by sganiev          ###   ########.fr       */
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
	int	mode;

	if (type == 3 || type == 6)
	{
		mode = O_CREAT | O_WRONLY | (type == 6) * O_APPEND
			| (type == 3) * O_TRUNC;
		redir_files_lstadd(&((*group)->f_out),
			create_redir_file(file, mode, STDOUT_FILENO));
	}
	else
	{
		if (type == HEREDOC)
		{
			(*group)->is_heredoc_in = handle_heredoc(rdr.l, file,
					&((*group)->heredoc_strs), rdr.envp);
			return (free_str(&file));
		}
		redir_files_lstadd(&((*group)->f_in),
			create_redir_file(file, O_RDONLY, STDIN_FILENO));
		reset_heredoc_fields(*group);
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
	while (*temp && (*temp)->type == SPC)
		*temp = (*temp)->next;
	while (*temp && p_command_h_one(*temp))
		*temp = (*temp)->next;
	while (*temp && (*temp)->type == SPC)
		*temp = (*temp)->next;
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
			p_redir_h_two(rdr, redir->type, &group, prepare_for_redir(&temp));
		p_redir_h_four(&temp);
	}
	*tokens = temp;
}
