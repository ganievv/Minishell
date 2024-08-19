/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_seven.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 22:05:41 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 07:06:28 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_ready_for_parsing(int l, t_token **src, t_token **dest,
			char **envp)
{
	token_to_token_preexp(*src, dest);
	token_preexp_to_trimed(dest);
	token_preexp_to_token_exp(l, dest, envp);
}

// tokenize src
// expand	src
// update   input
// tokenize udated input
// ==============================================
// parse	
// excecute

void	token_preexp_and_update_input(char **input, t_token *dest)
{
	char	*temp;
	char	*current;

	current = malloc(1);
	current[0] = '\0';
	temp = current;
	while (dest)
	{
		temp = ft_strjoin(current, dest->token_start);
		free(current);
		current = ft_strdup(temp);
		free(temp);
		dest = dest->next;
	}
	*input = current;
}
