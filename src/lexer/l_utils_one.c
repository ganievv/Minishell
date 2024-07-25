/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/24 20:42:52 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//ft_isspace is already given

// redir: >>, <<
// len 2
int	redir(char *str, int i)
{
	return (str[i] && str[i] == '<'
		&& str[i + 1] == '<'
		&& (!str[i + 2] || (str[i + 2] && str[i + 2] != '<')));
}

//''
int	is_quoted(char *str, int i)
{
	if (str[i] == 39)
		while (str[++i] && str[i] != 39)
			;
	return (str[i] == 39);
}

//""
int	is_d_quoted(char *str, int i)
{
	if (str[i] == 34)
		while (str[++i] && str[i] != 34)
			;
	return (str[i] == 34);
}

// I'll combine all the seperators
// spaces || double_lower_bigger || pipe_lower_bigger ||
// single_quotes || double_quotes || is_var

// $HOME or "go      to the directory $HOME" 