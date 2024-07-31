/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:13:11 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/31 17:49:22 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_h_escape(char *input, int *i, int *len)
{
	char	*valid_escape;

	(*i)++ ;
	if (input[*i] == '\0')
	{
		(*len)++ ;
		return ;
	}
	valid_escape = "nt\\\'\"";
	(*i)++ ;
	if (ft_strchr(valid_escape, input[*i]))
		*len += 1;
	else
		*len += 2;
	(*i)++;
}