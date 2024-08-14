/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:46:51 by tnakas            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/14 14:35:04 by tnakas           ###   ########.fr       */
=======
/*   Updated: 2024/08/14 02:53:03 by tnakas           ###   ########.fr       */
>>>>>>> parent of 1086d2d... making the correction in the parser
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
	char	*temp_str;
	char	*temp_join;
	t_token	*temp;

	args = NULL;
	arg_count = 0;
	current = NULL;
	temp_str = NULL;
	temp_join = NULL;
	temp = (*tokens);
	while ((temp) && ((temp)->type == 1))
		(temp) = (temp)->next;
	if (p_command_h_one(temp))
	{
		current = temp;
		temp_str = temp->token_start;
		temp = current->next;
		while (temp && (temp->type != 1))
		{
			temp_join = ft_strjoin(temp_str, temp->token_start);
			if (!temp_join)
				exit (1);
			free(temp_str);
			temp_str = temp_join;
			temp = temp->next;
		}
		group->command = temp_str;
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
		temp_str = temp->token_start;
		temp = current->next;
		while (temp && (temp->type != 1))
		{
			temp_join = ft_strjoin(temp_str, temp->token_start);
			if (!temp_join)
				exit (1);
			free(temp_str);
			temp_str = temp_join;
			temp = temp->next;
		}
		args[arg_count] = temp_str;
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
