/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:45 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/04 21:21:29 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_tokens(t_token *tokens, char **envp)
{
	t_token		*current;
	char		*expanded_content;

	expanded_content = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == EXP_FIELD)
			expanded_content = var_exp(current->token_start, envp);
		else if (current->type == D_QUOTED)
			expanded_content = var_d_quoted_exp(current->token_start, envp);
		else if (current->type == WORD)
			expanded_content = var_unquoted_exp(current->token_start, envp);
		if (!expanded_content)
			return ;
		if (expanded_content)
		{
			current->token_start = expanded_content;
			current->len = (int)ft_strlen(expanded_content);
		}
	}
}

char	*var_exp(char *input, char **envp)
{
	char	*var_name;
	int		i;
	char	*res;

	if (input[0] != '$')
		return (NULL);
	var_name = input + 1;
	i = -1;
	while (envp[++i])
	{
		if ((ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0)
			&& (envp[i][strlen(var_name)] == '='))
		{
			res = strdup(envp[i] + ft_strlen(var_name) + 1);
			if (!res)
				return (NULL);
			return (strdup(envp[i] + ft_strlen(var_name) + 1));
		}
	}
	res = strdup("");
	if (!res)
		return (NULL);
	return (strdup(""));
}

char	*var_unquoted_exp(char *input, char **envp)
{
	if (input[0] == '$')
		return (var_exp(input, envp));
	else
		return (strdup(input));
}
