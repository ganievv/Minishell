/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:58:50 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/09 15:02:00 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* clear screen before prompt */
void	clear_screen(void)
{
	printf("\033[H\033[J");
}

int	is_input_empty(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (0);
		input++;
	}
	return (1);
}
