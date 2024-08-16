/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:57:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/16 20:02:09 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static volatile sig_atomic_t	sigint_received = 0;

void	handle_sigint_heredoc(int signal)
{
	(void)signal;
	sigint_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static bool	create_pipe(bool *is_opened, int *p)
{
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
	char		*temp_str;

	if (!create_pipe(&is_opened, p))
		return (false);
	while (true)
	{
		rl_on_new_line();
		signal(SIGINT, handle_sigint_heredoc);
		str = readline(GRAY"> "RESET);
		signal(SIGINT, SIG_IGN);
		if (sigint_received)
		{
			sigint_received = 0;
			break ;
		}
		if (!str || (ft_strcmp(str, end) == 0))
			break ;
		if (ft_strchr(str, '$'))
		{
			temp_str = expand_double_quoted(l, str, envp);
			if (str)
				free(str);
			str = ft_strdup(temp_str);
			if (temp_str)
				free(temp_str);
		}
		write(p[1], str, ft_strlen(str));
		write(p[1], "\n", 1);
		free(str);
	}
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
