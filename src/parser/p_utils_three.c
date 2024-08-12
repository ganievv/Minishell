/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:57:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/12 16:02:38 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// handle env vars expansion
void	handle_heredoc(char *end, int *p)
{
	char	*str;
	char	new_line;

	str = NULL;
	if (pipe(p) == -1)
		return ;
	while (true)
	{
		str = readline(GRAY"> "RESET);
		if (!str)
			break ;
		if (ft_strcmp(str, end) == 0)
			break ;
		write(p[1], str, ft_strlen(str));
		write(p[1], "\n", 1);
		free(str);
	}
	read(p[0], new_line, 1);
	close(p[1]);
	if (str)
		free(str);
}

void	create_file(char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0666);
	if (fd == -1)
		return ;
	close(fd);
}
