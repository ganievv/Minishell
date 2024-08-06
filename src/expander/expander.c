/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:45 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/06 18:44:34 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_var(char *input, char **envp)
{
	int		i;
	char	*var_name;

	var_name = input + 1;
	i = -1;
	if (input[0] != '$')
		return (ft_strdup(input));
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
			&& envp[i][ft_strlen(var_name)] == '=')
			return (ft_strdup(envp[i] + ft_strlen(var_name) + 1));
	}
	return (ft_strdup(""));
}

void	expand_parsed_commands(t_pipe_group *group, char **envp)
{
	int		i;
	char	*expanded_content;

	expanded_content = NULL;
	while (group)
	{
		i = -1;
		while (group->args[++i])
		{
			if (group->args[i][0] == '$')
				expanded_content = expand_var(group->args[i], envp);
			else if (group->args[i][0] == '\"')
				expanded_content = expand_double_quoted(group->args[i], envp);
			else
				expanded_content = expand_unquoted(group->args[i], envp);
			if (expanded_content)
			{
				free(group->args[i]);
				group->args[i] = expanded_content;
			}
		}
		group = group->next;
	}
}

char	*expand_unquoted(char *input, char **envp)
{
	return (expand_var(input, envp));
}

// int main() {
//     char *input = "echo $USER $HOME \"$USER $HOME making changes\"";
//     t_token *head = NULL;

//     tokenize(input, &head);            // Step 1: Tokenize the input
//     t_pipe_group *group = parse(head); // Step 2: Parse the tokens

//     expand_parsed_commands(group, environ); // Step 3: Expand variables in parsed commands

//     // Print the parsed and expanded commands
//     t_pipe_group *current = group;
//     while (current) {
//         print_pipe_group(current);
//         current = current->next;
//     }

//     //Free allocated memory for parsed commands
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

//     // Free the tokens
//     // t_token *current_token = head;
//     // while (current_token) {
//     //     t_token *next = current_token->next;
//     //     free(current_token->token_start);
//     //     free(current_token);
//     //     current_token = next;
//     // }

//     return 0;
// }
