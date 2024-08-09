/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:57:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/09 19:32:32 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc(char *end, int *p)
{
	char	*str;

	str = NULL;
	if (pipe(p) == -1)
		return ;
	while (true)
	{
		str = readline("\x1b[90m> \x1b[0m");
		if (!str)
			break ;
		if (ft_strcmp(str, end) == 0)
			break ;
		// handle env vars
		write(p[1], str, ft_strlen(str));
		// write(p[1], "\n", 1);
		free(str);
	}
	if (str)
		free(str);
}
