/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:37:12 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/30 16:25:32 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	len_escape(char *rl, int *i, int *len)
{
	*len = 0;
	while (rl[*i])
	{
		if (rl[*i] == '\\' && rl[*i + 1] != '\0')
		{
			(*i)++;
			(*len)++;
		}
		(*i)++;
		(*len)++;
		if (ft_isspace(rl[*i]) || simple_separators(rl[*i]))
			break ;
	}
}

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

t_token	*token_new(char *rl, int i, int len)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->token_start = rl + i;
	new->len = len;
	new->type = token_find_type(rl, i, len);
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
