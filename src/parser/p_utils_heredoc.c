/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 22:20:29 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/19 23:28:28 by tnakas           ###   ########.fr       */
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
		*str = NULL;
		*str = ft_strdup(temp_str);
		free(temp_str);
		temp_str = NULL;
	}
}

void	copy_stdin_fd(int *stdin_copy)
{
	*stdin_copy = dup(STDIN_FILENO);
}

void	restore_stdin_fd(int stdin_copy, char **heredoc_strs)
{
	if (errno == EBADF)
	{
		dup2(stdin_copy, STDIN_FILENO);
		if (*heredoc_strs)
			free(*heredoc_strs);
		*heredoc_strs = NULL;
	}
	close(stdin_copy);
}

void	save_heredoc_str(char *str, char **heredoc_strs)
{
	char	*new_str;
	char	*tmp;

	new_str = ft_strjoin(str, "\n");
	free(str);
	str = NULL;
	if (!new_str)
		return ;
	tmp = *heredoc_strs;
	*heredoc_strs = ft_strjoin(*heredoc_strs, new_str);
	if (!*heredoc_strs)
		*heredoc_strs = ft_strdup("");
	free(tmp);
	tmp = NULL;
	free(new_str);
	new_str = NULL;
}
