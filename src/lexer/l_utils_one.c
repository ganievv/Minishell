/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/09 18:23:12 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_seperator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

t_token_type	token_type(char *str, int len)
{
	if (len == 1)
	{
		if (str[0] == '|')
			return (PIPE);
		if (str[0] == '<')
			return (REDIR_IN);
		if (str[0] == '>')
			return (REDIR_OUT);
		if (is_quote(str[0]) && str[0] == '\'')
			return (S_QUOTED);
		if (is_quote(str[0]) && str[0] == '\"')
			return (D_QUOTED);
	}
	if (len == 2 && (ft_strncmp(str, ">>", 2) == 0))
		return (APPEND_DELIMITER);
	if (len == 2 && (ft_strncmp(str, "<<", 2) == 0))
		return (DELIMITER);
	return (WORD);
}
