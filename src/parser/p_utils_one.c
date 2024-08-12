/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:47:27 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/13 00:41:28 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	parse_redir_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == REDIR_IN
			|| tokens->type == REDIR_OUT
			|| tokens->type == APPEND_DELIMITER
			|| tokens->type == HEREDOC));
}

static void	parse_redir_h_two(t_token_type type,
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
			if (handle_heredoc(file, (*group)->heredoc_p))
				(*group)->is_heredoc_in = true;
			return ;
		}
		(*group)->file_in = file;
		(*group)->redir_in = STDIN_FILENO;
		(*group)->mode_in = O_RDONLY;
		close_read_end(*group);
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
	while (parse_redir_h_one(temp))
	{
		type = temp->type;
		temp = temp->next;
		if (temp && temp->type == WORD)
		{
			file = token_content_extract(temp);
			if (!file)
				return ;
			parse_redir_h_two(type, &group, file);
			temp = temp->next;
		}
	}
	*tokens = temp;
}

/* should we free here 'command', 'file_in', 'file_out' ?*/
void	pipe_group_free(t_pipe_group **head)
{
	t_pipe_group	*current;
	t_pipe_group	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free_arr_str(current->args);
		free_arr_str(current->argv);
		if (current->cmd_path)
			free(current->cmd_path);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	pipe_group_print(t_pipe_group *group)
{
	int	i;

	while (group)
	{
		printf("Command: %s\n", group->command);
		printf("Arguments:\n");
		i = -1;
		while (group->args && group->args[++i])
			printf("  [%d]: %s\n", i, group->args[i]);
		group = group->next;
	}
}
