/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:57:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/21 13:54:05 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	prepare_heredoc_redir(char **heredoc_strs, int *stdin_copy)
{
	copy_stdin_fd(stdin_copy);
	if (*stdin_copy == -1)
		return (false);
	if (*heredoc_strs)
		free(*heredoc_strs);
	*heredoc_strs = ft_strdup("");
	if (!*heredoc_strs)
		return (false);
	return (true);
}

bool	handle_heredoc(int l, char *end, t_pipe_group *group, char **envp)
{
	char	*str;
	int		stdin_copy;

	if (!prepare_heredoc_redir(&(group->heredoc_strs), &stdin_copy))
		return (false);
	while (true)
	{
		rl_on_new_line();
		signal(SIGINT, handle_sigint_heredoc);
		str = readline("> ");
		signal(SIGINT, SIG_IGN);
		if (!str || (ft_strcmp(str, end) == 0))
			break ;
		if (!group->is_heredoc_quoted)
			expand_heredoc_strs(&str, l, envp);
		save_heredoc_str(str, &(group->heredoc_strs));
	}
	restore_stdin_fd(stdin_copy, &(group->heredoc_strs));
	if (str)
		free(str);
	return (true);
}

void	reset_heredoc_fields(t_pipe_group *cmd)
{
	if (cmd->heredoc_strs)
		free(cmd->heredoc_strs);
	cmd->heredoc_strs = NULL;
	cmd->is_heredoc_in = false;
}

void	print_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		printf("str[%d] = %s\n", i, str[i]);
	printf("(null)\n");
}
