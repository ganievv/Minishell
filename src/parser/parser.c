/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:28:51 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/16 19:41:00 by tnakas           ###   ########.fr       */
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
	new_group->is_heredoc_in = false;
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

t_pipe_group	*parse_pipeline(int l, t_token **tokens, char **envp)
{
	t_pipe_group	*head;
	t_pipe_group	*current;
	t_pipe_group	*group;
	t_token			*token_start;

	head = NULL;
	current = NULL;
	token_start = NULL;
	while (*tokens)
	{
		token_start = *tokens;
		group = pipe_group_init();
		while (*tokens && (*tokens)->type == SPC)
			(*tokens) = (*tokens)->next;
		parse_command(tokens, group);
		parse_args(&(*tokens), group);
		parse_redir(l, &token_start, group, envp);
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
		if (*tokens && (*tokens)->type == 2)
			*tokens = (*tokens)->next;
	}
	return (head);
}

t_pipe_group	*parse(int l, t_token *tokens, char **envp)
{
	return (parse_pipeline(l, &tokens, envp));
}

// int main() {
//     char *input = "echo Hello World | echo  World $HOME";
//     t_token *head = NULL;

//     // Tokenize the input
//     tokenize(input, &head);
//     print_tokens(head);

//     // Parse the tokens into pipe groups
//     t_pipe_group *group = parse_pipeline(&head);

//     // Print the parsed pipe groups
//     t_pipe_group *current = group;
//     while (current) {
//         pipe_group_print(current);
//         current = current->next;
//     }

//     // Free the tokens
//     t_token *token_current = head;
//     while (token_current) {
//         t_token *next = token_current->next;
//         free(token_current);
//         token_current = next;
//     }

//     // Free the pipe groups
//     while (group) {
//         t_pipe_group *tmp = group;
//         group = group->next;
//         if (tmp->args) {
//             for (int i = 0; tmp->args[i]; i++) {
//                 free(tmp->args[i]);
//             }
//             free(tmp->args);
//         }
//         free(tmp);
//     }

//     return 0;
// }

// int main() {
//     // Example tokens for testing different types
//     t_token token6 = {"world", 5, WORD, NULL};
//     t_token token5 = {"out.txt", 7, WORD, &token6};
//     t_token token4 = {">", 1, REDIR_OUT, &token5};
//     t_token token3 = {"|", 1, PIPE, &token4};
//     t_token token2 = {"\"HOME\"", 5, EXP_FIELD, &token3};
//     t_token token1 = {"cd", 2, WORD, &token2};

//     // Parsing tokens into pipe groups
//     t_pipe_group *group = parse(&token1);

//     // Printing the parsed pipe groups
//     t_pipe_group *current = group;
//     while (current) {
//         pipe_group_print(current);
//         current = current->next;
//     }

//     // Freeing the pipe groups
//     while (group) {
//         t_pipe_group *tmp = group;
//         group = group->next;
//         if (tmp->args) {
//             for (int i = 0; tmp->args[i]; i++) {
//                 free(tmp->args[i]);
//             }
//             free(tmp->args);
//         }
//         free(tmp);
//     }

//     return 0;
// }
