/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 19:46:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/16 15:16:18 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../../include/minishell.h"

int	p_command_h_one(t_token *tokens)
{
	return (tokens && (tokens->type == WORD || tokens->type == EXP_FIELD
			|| tokens->type == D_QUOTED || tokens->type == S_QUOTED));
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
	//printf("%s\n", current_str);
}

void	parse_args(t_token **tokens, t_pipe_group *group)
{
	t_token	*temp;
	// t_token	*redir;
	char	*temp_str;
	char	*current_str;
	char	**args;
	int		i;

	temp = *tokens;
	current_str = NULL;
	temp_str = NULL;
	args = NULL;
	i = 0;
	while (temp && temp->type != PIPE)
	{
		while (p_command_h_one(temp) || (temp && p_redir_h_one(temp)))
		{
			//printf("here 1\n");
			if (temp && p_redir_h_one(temp))
			{
				temp = temp->next;
				//printf("here 2\n");
				while (temp && temp->type == SPC)
					temp = temp->next;
				if (p_command_h_one(temp))
				{
					//printf("redir friend\n");
					temp = temp->next;
				}
			}
			current_str = NULL;
			while (p_command_h_one(temp))
			{
				//printf("here 3\n");
				if (!current_str)
				{
					current_str = ft_strdup(temp->token_start);
					//printf("here 4\n");
				}
				else
				{
					temp_str = ft_strjoin(current_str, temp->token_start);
					free(current_str);
					current_str = temp_str;
					//printf("here 5\n");
				}
				//printf("here 6\n");
				if (temp)
					temp = temp->next;
			}
			//printf("here 7\n");
			if (current_str)
			{
				if (args)
					args = ft_realloc(args, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
				else
					args = (char **)malloc(sizeof(char *) * 2);
				args[i] = ft_strdup(current_str);
				i++;
				args[i] = NULL;
				free(current_str);
				//printf("here 8\n");
			}
			while (temp && temp->type == SPC)
				temp = temp->next;
		}
	}

	group->args = args;
	(*tokens) = temp;
}

// int	p_command_h_two(t_token *tokens)
// {
// 	return (tokens->type == SPC);
// }

// void	parse_command(t_token **tokens, t_pipe_group *group)
// {
// 	char	**args;
// 	int		arg_count;
// 	t_token	*current;
// 	char	*temp_str;
// 	char	*temp_join;
// 	t_token	*temp;

// 	args = NULL;
// 	arg_count = 0;
// 	current = NULL;
// 	temp_str = NULL;
// 	temp_join = NULL;
// 	temp = (*tokens);
// 	while ((temp) && ((temp)->type == 1))
// 		(temp) = (temp)->next;
// 	if (p_command_h_one(temp))
// 	{

// 		current = temp;
// 		temp_str = temp->token_start;
// 		temp = current->next;
// 		while ((p_command_h_one(temp)))
// 		{
// 			temp_join = ft_strjoin(temp_str, temp->token_start);
// 			free(temp_str);
// 			temp_str = temp_join;
// 			temp = temp->next;
// 		}
// 		group->command = temp_str;
// 	}
// 	while (p_command_h_one(temp) || (temp && temp->type == 1))
// 	{
// 		if ((temp)
// 			&& ((((temp)->type == 8 || (temp)->type == 7)
// 					&& (temp)->len == 2)|| (temp->type == 1)))
// 		{
// 			(temp) = (temp)->next;
// 			continue ;
// 		}
//		args = ft_realloc(args, sizeof(char *) * (arg_count),
// 				sizeof(char *) * (arg_count + 2));
// 		if (!args)
// 			exit(1);
// 		current = temp;
// 		temp_str = temp->token_start;
// 		temp = current->next;
// 		while (p_command_h_one(temp))
// 		{
// 			temp_join = ft_strjoin(temp_str, temp->token_start);
// 			free(temp_str);
// 			temp_str = temp_join;
// 			temp = temp->next;
// 		}
// 		args[arg_count] = temp_str;
// 		if (!args[arg_count])
// 			exit(1);
// 		args[arg_count + 1] = NULL;
// 		arg_count++;
// 		if (temp)
// 			temp = (temp)->next;
// 	}
// 	group->args = args;
// 	*tokens = temp;
// }
