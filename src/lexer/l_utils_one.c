/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/24 15:45:14 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//ft_isspace is already given

//<< or >>
int	ft_isdouble_lower_bigger(char *str, int i)
{
	return (str[i] && ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>')));
}

//|><
int	ft_is_pipe_lower_bigger(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

//''
int	ft_is_quoted(char *str, int i)
{
	if (str[i] == 39)
		while (str[++i] && str[i] != 39)
			;
	return (str[i] == 39);
}

//""
int	ft_is_dquoted(char *str, int i)
{
	if (str[i] == 34)
		while (str[++i] && str[i] != 34)
			;
	return (str[i] == 34);
}

//$ without checking if it's unquoted, in double quotes or in single quotes
int	ft_isvar(char c)
{
	return (c == '$');
}
// I'll combine all the seperators
// spaces || double_lower_bigger || pipe_lower_bigger ||
// single_quotes || double_quotes || is_var

// $HOME or "go      to the directory $HOME" 