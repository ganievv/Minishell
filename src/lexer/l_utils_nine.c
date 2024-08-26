/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils_nine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 01:55:36 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/21 14:19:49 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	first_second_third(t_token **dest)
{
	if (!dest || !*dest)
		return ;
	if ((*dest)->type == HEREDOC)
	{
		*dest = (*dest)->next;
		if (!*dest)
			return ;
		while (*dest && (*dest)->type == SPC)
			*dest = (*dest)->next;
		while (*dest && p_command_h_one(*dest))
			*dest = (*dest)->next;
	}
}

char	*prepare_for_redir(t_pipe_group *group, t_token **token)
{
	char	*res;
	char	*temp;
	t_token	*temp_t;

	temp_t = (*token);
	res = ft_strdup("\0");
	temp = NULL;
	while (temp_t && p_command_h_one(temp_t))
	{
		if (temp_t->type == S_QUOTED || temp_t->type == D_QUOTED)
			group->is_heredoc_quoted = true;
		temp = res;
		res = ft_strjoin(res, temp_t->token_start);
		free_str(&temp);
		temp_t = temp_t->next;
	}
	*token = temp_t;
	return (res);
}
