/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_eight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 05:14:21 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/21 15:14:59 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_to_token_preexp(t_token *src, t_token **dest)
{
	while (src)
	{
		token_lstadd(dest, token_create_preexp(src->token_start,
				src->len, src->type));
		src = src->next;
	}
}

//&& temp->token_start[0] != '\0'
void	token_preexp_free(t_token **head)
{
	t_token	*current;
	t_token	*next_token;

	if (!head || !*head)
		return ;
	current = (*head);
	next_token = NULL;
	while (current)
	{
		next_token = current->next;
		free_str(&(current->token_start));
		free(current);
		current = next_token;
	}
	*head = NULL;
}

void	token_preexp_to_trimed(t_token **dest)
{
	t_token	*temp;
	char	*temp_str;

	temp = *dest;
	while (temp)
	{
		if (temp->type == 8 || temp->type == 7)
		{
			if (ft_strlen(temp->token_start) > 2)
				temp_str = ft_strndup(temp->token_start + 1,
						ft_strlen(temp->token_start) - 2);
			else
				temp_str = ft_strdup("\0");
			if (!temp_str)
			{
				token_preexp_free(dest);
				return ;
			}
			free(temp->token_start);
			temp->token_start = temp_str;
		}
		temp = temp->next;
	}
}

void	token_preexp_to_token_exp(int l, t_token **dest, char **envp)
{
	t_token	*temp;
	char	*temp_str;

	temp = *dest;
	while (temp)
	{
		first_second_third(&temp);
		if (temp && (temp->type == EXP_FIELD || ((temp->type == D_QUOTED)
					&& ft_strchr(temp->token_start, '$'))))
		{
			if (temp->type == EXP_FIELD)
				temp_str = expand_var(l, temp->token_start, envp);
			else
				temp_str = expand_double_quoted(l, temp->token_start, envp);
			if (!temp_str)
				token_preexp_free(dest);
			free(temp->token_start);
			temp->token_start = NULL;
			temp->token_start = temp_str;
			temp->len = -1;
		}
		if (temp)
			temp = temp->next;
	}
}
