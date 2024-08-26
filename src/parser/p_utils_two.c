/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:46:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/21 15:00:50 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../include/minishell.h"

void	p_args_skip_spaces(t_token **temp)
{
	if (!temp || !*temp)
		return ;
	if (p_redir_h_one((*temp)))
	{
		*temp = (*temp)->next;
		if (!*temp)
			return ;
		while (*temp && (*temp)->type == SPC)
			*temp = (*temp)->next;
		while (*temp && p_command_h_one(*temp))
			*temp = (*temp)->next;
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

static void	pre_command_phase(t_token **tokens)
{
	t_token	*temp;

	if (!tokens || !(*tokens))
		return ;
	temp = *tokens;
	while (temp && temp->type == SPC)
		temp = temp->next;
	while (temp && p_redir_h_one(temp))
	{
		temp = temp->next;
		while (temp && temp->type == SPC)
			temp = temp->next;
		if (temp && temp->type == PIPE)
			break ;
		while (temp && p_command_h_one(temp))
			temp = temp->next;
		while (temp && temp->type == SPC)
			temp = temp->next;
		if (temp && temp->type == PIPE)
			break ;
	}
	*tokens = temp;
}

void	parse_command(t_token **tokens, t_pipe_group *group)
{
	t_token			*temp;
	char			*temp_str;
	char			*current_str;

	temp = *tokens;
	current_str = NULL;
	pre_command_phase(&temp);
	while (temp && p_command_h_one(temp))
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
	group->command = current_str;
	while (temp && temp->next && (temp->type == SPC))
		temp = temp->next;
	(*tokens) = temp;
}
