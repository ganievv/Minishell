/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:46:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/18 00:51:53 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../include/minishell.h"

static void	p_args_skip_spaces(t_token **temp)
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

static void	join_command_str(t_token **temp, char **current_str)
{
	char	*temp_str;

	*current_str = NULL;
	while (*temp && p_command_h_one(*temp))
	{
		if (!*current_str)
			*current_str = ft_strdup((*temp)->token_start);
		else
		{
			temp_str = ft_strjoin(*current_str, (*temp)->token_start);
			//after
			free(*current_str);
			*current_str = temp_str;
		}
		*temp = (*temp)->next;
	}
}

static void	add_arg_and_skip_spaces(char ***args, char *current_str,
	t_token **temp, int *i)
{
	if (current_str)
	{
		if ((*args))
			(*args) = ft_realloc((*args), sizeof(char *) * (*i + 1),
					sizeof(char *) * (*i + 2));
		else
			(*args) = (char **)malloc(sizeof(char *) * 2);
		(*args)[*i] = ft_strdup(current_str);
		(*i)++;
		(*args)[*i] = NULL;
		free(current_str);
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

void	parse_args(t_token **tokens, t_pipe_group *group)
{
	t_token	*temp;
	char	*current_str;
	char	**args;
	int		i;

	temp = *tokens;
	current_str = NULL;
	args = NULL;
	i = 0;
	while (temp && temp->type == SPC)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		while (temp && (p_command_h_one(temp) || p_redir_h_one(temp)))
		{
			p_args_skip_spaces(&temp);
			join_command_str(&temp, &current_str);
			add_arg_and_skip_spaces(&args, current_str, &temp, &i);
		}
	}
	group->args = args;
	(*tokens) = temp;
}
