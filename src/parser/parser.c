/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:28:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/03 13:28:08 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_pipe_group	*pipe_group_init(void)
{
	t_pipe_group	*new_group;

	new_group = (t_pipe_group *)malloc(sizeof(t_pipe_group));
	if (!new_group)
		return (NULL);
	new_group->command = NULL;
	new_group->args = NULL;
	new_group->file_in = NULL;
	new_group->file_out = NULL;
	new_group->redir_in = 0;
	new_group->redir_out = 0;
	new_group->mode_in = 0;
	new_group->mode_out = 0;
	new_group->argv = NULL;
	new_group->cmd_path = NULL;
	new_group->next = NULL;
	return (new_group);
}

void	pipe_group_add(t_pipe_group **head, t_pipe_group *new_group)
{
	t_pipe_group	*temp;

	if (!head || !new_group)
		return ;
	temp = *head;
	if (!*head)
		*head = new_group;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_group;
	}
}

void	parse_command(t_token **tokens, t_pipe_group *group)
{
	char	**args;
	int		arg_count;

	args = NULL;
	arg_count = 0;
	while (*tokens && (*tokens)->type == WORD)
	{
		args = ft_realloc(args, sizeof(char *) * (arg_count),
				sizeof(char *) * (arg_count + 2));
		if (!args)
			exit(1);
		args[arg_count] = token_content_extract(*tokens);
		if (!args[arg_count])
			exit(1);
		args[arg_count + 1] = NULL;
		arg_count++;
		*tokens = (*tokens)->next;
	}
	if (args)
		group->command = args[0];
	else
		group->command = NULL;
	group->args = args;
}

t_pipe_group	*parse_pipeline(t_token **tokens)
{
	t_pipe_group	*head;
	t_pipe_group	*current;
	t_pipe_group	*group;

	head = NULL;
	current = NULL;
	while (*tokens)
	{
		group = pipe_group_init();
		parse_command(tokens, group);
		parse_redirection(tokens, group);
		if (!head)
		{
			head = group;
			current = head;
		}
		else
		{
			current->next = group;
			current = current->next;
		}
		if (*tokens && (*tokens)->type == PIPE)
			*tokens = (*tokens)->next;
	}
	return (head);
}

t_pipe_group	*parse(t_token *tokens)
{
	return (parse_pipeline(&tokens));
}
