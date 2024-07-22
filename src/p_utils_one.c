/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/22 16:03:51 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ft_isspace is already given

//<< or >>
int	ft_isdouble_lower_bigger(char *str, int i)
{
	return (str[i] && ((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>')));
}

//|><
int	ft_issingle_pipe_lower_bigger(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

//''
int ft_issingle_quote(char *str, int i)
{
	if (str[i] ==  39)
		while (str[++i] && str[i] != 39)
			;
	return(str[i] == 39);
}

//""
int ft_isdouble_quote(char *str, int i)
{
	if (str[i] ==  34)
		while (str[++i] && str[i] != 34)
			;
	return(str[i] == 34);
}

//$ without checking if it's unquoted, in double quotes or in single quotes
int	ft_isvar_simple(char c)
{
	return (c == '$');
}
//if it's unquoted or inside double_quotes
//if it's double quoted  && an $ is existing
int	ft_isdouble_quote_var(char *str, int i)
{
		if (ft_isdouble_quote_var(str, i))
			while (str[++i] && str[i] != 34)
				if (str[i] == '$')
					 return (1);
		return (0);
}
// $HOME or "go      to the directory $HOME" 