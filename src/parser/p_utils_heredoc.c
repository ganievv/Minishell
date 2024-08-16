/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 22:20:29 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/16 22:35:52 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_heredoc_strs(char **str, int l, char **envp)
{
	char	*temp_str;

	if (ft_strchr(*str, '$'))
	{
		temp_str = expand_double_quoted(l, *str, envp);
		if (!temp_str)
			return ;
		free(*str);
		*str = ft_strdup(temp_str);
		free(temp_str);
	}
}

void	copy_stdin_fd(int *stdin_copy)
{
	*stdin_copy = dup(STDIN_FILENO);
}

void	restore_stdin_fd(int stdin_copy)
{
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
}
