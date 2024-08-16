/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:57:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/16 20:02:09 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	prepare_heredoc_redir(bool *is_opened, int *p, int *stdin_copy)
{
	copy_stdin_fd(stdin_copy);
	if (*stdin_copy == -1)
		return (false);
	if (*is_opened)
	{
		close(p[0]);
		*is_opened = false;
	}
	if (pipe(p) == -1)
		return (false);
	*is_opened = true;
	return (true);
}

// handle env vars expansion
bool	handle_heredoc(int l, char *end, int *p, char **envp)
{
	static bool	is_opened = false;
	char		*str;
	int			stdin_copy;

	if (!prepare_heredoc_redir(&is_opened, p, &stdin_copy))
		return (false);
	while (true)
	{
		rl_on_new_line();
		signal(SIGINT, handle_sigint_heredoc);
		str = readline(GRAY"> "RESET);
		signal(SIGINT, SIG_IGN);
		if (!str || (ft_strcmp(str, end) == 0))
			break ;
		expand_heredoc_strs(&str, l, envp);
		write(p[1], str, ft_strlen(str));
		write(p[1], "\n", 1);
		free(str);
	}
	restore_stdin_fd(stdin_copy);
	close(p[1]);
	if (str)
		free(str);
	return (true);
}

void	create_file(char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0666);
	if (fd == -1)
		return ;
	close(fd);
}

void	close_read_end(t_pipe_group *cmd)
{
	if (cmd->is_heredoc_in)
		close(cmd->heredoc_p[0]);
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
