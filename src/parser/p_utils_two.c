/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:46:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/13 21:13:20 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	p_command_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == WORD || tokens->type == EXP_FIELD
			|| tokens->type == D_QUOTED || tokens->type == S_QUOTED));
}

int	p_command_h_two(t_token *tokens)
{
	return (tokens->type == SPC);
}

void	parse_command(t_token **tokens, t_pipe_group *group)
{
	char	**args;
	int		arg_count;
	t_token	*current;
	int		current_len;
	t_token	*temp;

	args = NULL;
	arg_count = 0;
	current = NULL;
	temp = (*tokens);
	while ((temp) && ((temp)->type == 1))
		(temp) = (temp)->next;
	if (p_command_h_one(temp))
	{

		current = temp;
		current_len = current->len;
		temp = current->next;
		while (temp && (temp->type != 1))
		{
			current->len += temp->len;
			temp = temp->next;
		}
		group->command = token_content_extract(current, current_len);
	}
	while (temp && ((temp)->type == 1))
		(temp) = (temp)->next;
	while (p_command_h_one(temp))
	{
		if ((temp)
			&& ((temp)->type == 8 || (temp)->type == 7)
			&& (temp)->len == 2)
		{
			(temp) = (temp)->next;
			continue ;
		}
		args = ft_realloc(args, sizeof(char *) * (arg_count),
				sizeof(char *) * (arg_count + 2));
		if (!args)
			exit(1);
		current = temp;
		current_len = current->len;
		temp = temp->next;
		while (temp && (temp->type != 1))
		{
			current_len += temp->len;
			temp = temp->next;
		}
		args[arg_count] = token_content_extract(current, current_len);
		if (!args[arg_count])
			exit(1);
		args[arg_count + 1] = NULL;
		arg_count++;
		if (temp)
			temp = (temp)->next;
	}
	group->args = args;
	*tokens = temp;
}
