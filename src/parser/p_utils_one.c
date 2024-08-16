/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:47:27 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/16 03:36:32 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	p_redir_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == REDIR_IN
			|| tokens->type == REDIR_OUT
			|| tokens->type == APPEND_DELIMITER
			|| tokens->type == HEREDOC));
}

void	parse_redir_h_two(t_token_type type,
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
			(*group)->is_heredoc_in = handle_heredoc(file,
					(*group)->heredoc_p);
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
	// I must stop only to redirs
	t_token	*temp;

	temp = *tokens;
	while(!p_redir_h_one(temp))
		temp = temp->next;
	if (p_redir_h_one(temp))
	{
		while (temp && temp->type == SPC)
			temp = temp->next;
	}
	*tokens = temp;
}
// void	parse_redir(t_token **tokens, t_pipe_group *group)
// {
// 	t_token_type	type;
// 	t_token			*temp;
// 	char			*file;
// 	int				first_time;

// 	type = -1;
// 	temp = *tokens;
// 	file = NULL;
// 	first_time = 1;
// 	while (temp && temp->type != PIPE)
// 	{
// 		while (temp && temp->type == SPC)
// 			temp = temp->next;
// 		while (p_redir_h_one(temp))
// 		{
// 			if (first_time)
// 				temp = temp->next;
// 			if (temp && temp->type == SPC)
// 			{
// 				temp = temp->next;
// 				continue ;
// 			}
// 			if (temp && temp->type == WORD)
// 			{
// 				if (file)
// 					free(file);
// 				file = NULL;
// 				file = token_content_extract(temp, temp->len);
// 				if (!file)
// 					return ;
// 				parse_redir_h_two(temp->type, &group, file);
// 				temp = temp->next;
// 			}
// 		}
// 	}
// 	*tokens = temp;
// }

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
