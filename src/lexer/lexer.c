/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:48:14 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 16:26:10 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//a function that is giving you back what type of enum is the string

t_token_type	token_find_type(char *str, int i, int len)
{
	char 			*temp;
	t_token_type	type;

	temp = ft_strndup(str + i, len);
	if (!temp)
		return (NULL);
	if (!ft_strcmp("<", temp))
		type = REDIR_IN;
	else if (!ft_strcmp(">", temp))
		type = REDIR_OUT;
	else if (!ft_strcmp("<<", temp))
		type = DELIMITER;
	else if (!ft_strcmp(">>", temp))
		type = APPEND_DELIMITER;
	else if (!ft_strcmp("|", temp))
		type = PIPE;
	else if (str[0] == 34 && str[ft_strlen(temp) - 1] == 34)
		type = DOUBLE_QUOTED;
	else if (str[0] == 39 && str[ft_strlen(temp) - 1] == 39)
		type = SINGLE_QUOTED;
	else if (temp[0] == '$')
		type = EXP_FIELD;
	else
		type = WORD;
	return (free(temp), type);
}

// how to add on the list
void	token_list(t_token **head, char *rl)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (rl[i] && ft_isspace(rl[i]))
		i++;
	while (rl[i])
	{
		if (redir(rl, i))
		{
			ft_lstadd_back(temp, token_new(rl + i, i, 2));
			i += 2;
		}
		else if (ft_isspace(rl[i]))
		{
			ft_lstadd_back(temp, token_new(rl + i, i, 1));
			isspace_skip(rl + i, &i);
		}
		else if (simple_seperators(rl + i))
		{
			ft_lstadd_back(temp, token_new(rl + i, i, 1));
			i++;
		}
		else if (rl[i] == '\'' || r[i] == '\"')
		{
			len_quoted(rl + i, &len);
			ft_lstadd_back(temp, token_new(rl + i, i, len));
			i += len;
		}
		else if (rl[i] == '$')
		{
			len_var(rl + i, &len);
			ft_lstadd_back(temp, token_new(rl + i, i, len));
			i += len;
		}
		else if (rl[i] == '\\')
		{
			len_escape(rl, &i, &len);
			ft_lstadd_back(head, token_new(rl, i - len, len));
		}
		else
		{
			len_words(rl + i, &len);
			ft_lstadd_back(temp, token_new(rl + i, i, len));
			i += len;
		}
	}
}
// I need on the spaces split
// on the | < > << >> $ "" '' and save them as they are
