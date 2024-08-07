/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:45 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/07 17:58:36 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_var(int l, char *input, char **envp)
{
	int		i;
	char	*var_name;
	char	*res;

	if (*input != '$')
		return (ft_strdup(input));
	if (*(input + 1) == '?')
	{
		res = ft_itoa(l);
		if (!res)
			return (NULL);
		return (res);
	}
	var_name = input + 1;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
			&& envp[i][ft_strlen(var_name)] == '=')
			return (ft_strdup(envp[i] + ft_strlen(var_name) + 1));
	}
	return (ft_strdup(""));
}

void	expand_parsed_commands(int l, t_pipe_group *group, char **envp)
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
				expanded_content = expand_var(l, group->args[i], envp);
			else if (group->args[i][0] == '\"')
				expanded_content = expand_double_quoted(l,
						group->args[i], envp);
			else
				expanded_content = expand_unquoted(l, group->args[i], envp);
			if (expanded_content)
			{
				free(group->args[i]);
				group->args[i] = expanded_content;
			}
		}
		group = group->next;
	}
}

char	*expand_unquoted(int l, char *input, char **envp)
{
	return (expand_var(l, input, envp));
}

//int main()
//{
//	char *input = "echo $USER $HOME \"$USER $HOME making changes\"";
//	t_token *head = NULL;

//	tokenize(input, &head);
//	t_pipe_group *group = parse(head);

//	expand_parsed_commands(group, environ);
//	t_pipe_group *current = group;
//	pipe_group_print(current);
//	pipe_group_free(&current);
//	token_free(&head);

//    return (0);
//}

// int main(int argc, char **argv, char **envp)
// {
// 	char *input = "echo $USER $? \"    $? $HOME making\"";
// 	t_token *head = NULL;
// 	int l = 255;
// 	tokenize(input, &head);
// 	(void)argc;
// 	(void)argv;
// 	t_pipe_group *group = parse(head);

// 	expand_parsed_commands(l, group, envp);
// 	t_pipe_group *current = group;
// 	pipe_group_print(current);
// 	pipe_group_free(&current);
// 	token_free(&head);

//     return (0);
// }
