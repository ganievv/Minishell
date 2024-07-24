/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:37:12 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/24 15:46:15 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isquote_dquote(char c)
{
	return (c = '\'' || c = '\"');
}

int	ft_isvar_dqoute(char *str, int i)
{
	if (ft_isvar(str[i]))
		while (str[++i] && str[i] != 34)
			if (str[i] == '$')
				return (1);
	return (0);
}

t_token	*token_new(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token_start = content;
	new->len = ft_strlen(content);
	new->type = token_find_type(content);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
