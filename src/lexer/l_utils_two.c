/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:37:12 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/04 21:35:56 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*token_create(char *start, int len, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->token_start = start;
	new_token->len = len;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

char	*token_content_extract(t_token *token)
{
	char	*res;

	res = ft_strndup(token->token_start, token->len);
	if (!res)
		return (NULL);
	return (res);
}

void	token_lstadd(t_token **head, t_token *new_token)
{
	t_token	*temp;

	temp = *head;
	if (!temp)
		*head = new_token;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}
