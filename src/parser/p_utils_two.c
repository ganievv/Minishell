/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:46:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 06:03:50 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../include/minishell.h"

void	p_args_skip_spaces(t_token **temp)
{
	if ((*temp) && p_redir_h_one((*temp)))
	{
		(*temp) = (*temp)->next;
		while ((*temp) && (*temp)->type == SPC)
			(*temp) = (*temp)->next;
		if (p_command_h_one((*temp)))
			(*temp) = (*temp)->next;
	}
}

void	join_command_str(t_token **temp, char **current_str)
{
	char	*temp_str;

	*current_str = NULL;
	while (*temp && p_command_h_one(*temp))
	{
		if (!*current_str)
			temp_str = ft_strdup((*temp)->token_start);
		else
			temp_str = ft_strjoin(*current_str,
					(*temp)->token_start);
		free(*current_str);
		if (!temp_str)
		{
			*current_str = NULL;
			return ;
		}
		*current_str = temp_str;
		*temp = (*temp)->next;
	}
}

void	add_arg_and_skip_spaces(char ***args, char *current_str,
	t_token **temp, int *i)
{
	if (current_str)
	{
		*args = args_join(*args, current_str);
		(*i)++;
	}
	while ((*temp) && (*temp)->type == SPC)
		(*temp) = (*temp)->next;
}

void	parse_command(t_token **tokens, t_pipe_group	*group)
{
	t_token	*temp;
	char	*temp_str;
	char	*current_str;

	temp = *tokens;
	current_str = NULL;
	while (p_command_h_one(temp))
	{
		if (!current_str)
			temp_str = ft_strdup(temp->token_start);
		else
			temp_str = ft_strjoin(current_str, temp->token_start);
		if (current_str)
			free(current_str);
		current_str = ft_strdup(temp_str);
		free(temp_str);
		if (temp)
			temp = temp->next;
	}
	while (temp && temp->next && ((p_command_h_one(temp)
				&& temp->token_start[0] == '\0') || temp->type == SPC))
		temp = temp->next;
	group->command = current_str;
	(*tokens) = temp;
}
