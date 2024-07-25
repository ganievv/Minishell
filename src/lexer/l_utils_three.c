/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:49 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/25 14:25:08 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//Simple_Seperators: "|, <, >, isspace"
// len 1
int	simple_seperators(char c)
{
	return (c == '\\' || c == '|'
		|| c == '<' || c == '>');
}

void	isspace_skip(char *rl, int *i)
{
	if (ft_isspace(rl[*i]))
		while (rl[++(*i)] && ft_isspace(rl[*i]))
			;
}

void	len_quoted(char *rl, int *len)
{
	(*len) = 0;
	if (is_quoted(rl, i) || is_d_quoted(rl, i))
	{
		(*len)++;
		if (is_quoted(rl, i))
			while (rl[++i] != '\'')
				(*len)++;
		else
			while (rl[++i] != '\"')
				(*len)++;
		return ;
	}
	while (!ft_isspace(rl[++i]))
		(*len)++;
}

// var
void	len_var(char *rl, int *len)
{
	(*len) = 0;
	*i--;
	while (!ft_isspace(rl[++*i]))
		(*len)++;
}

// words
int	len_words(char *rl, int *len)
{
	(*len) = 0;
	*i--;
	while (!ft_isspace(rl[++*i]))
		(*len)++;
}
