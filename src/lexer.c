/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/23 14:19:36 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//a function that is giving you back what type of enum is the string

t_token_type	token_find_type(char *str)
{
	if (!ft_strcmp("<", str))
		return (REDIR_IN);
	else if (!ft_strcmp(">", str))
		return (REDIR_OUT);
	else if (!ft_strcmp("<<", str))
		return (DELIMITER);
	else if (!ft_strcmp(">>", str))
		return (APPEND_DELIMITER);
	else if (!ft_strcmp("|", str))
		return (PIPE);
	else if (str[0] == 34 && str[ft_strlen(str) - 1] == 34)
		return (DOUBLE_QUOTED);
	else if (str[0] == 39 && str[ft_strlen(str) - 1] == 39)
		return (SINGLE_QUOTED);
	else if (!ft_strchr(str, 34) && !ft_strchr(str, 39) && ft_strchr(str, '$'))
		return (EXP_FIELD);
	else
		return (WORD);
}

// how to split
// I need on the spaces split
// on the | < > << >> $ "" '' and save them as they are
