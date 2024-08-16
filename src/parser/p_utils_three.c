/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 18:57:37 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/16 19:51:43 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// handle env vars expansion
bool	handle_heredoc(int l, char *end, int *p, char **envp)
{
	static bool	is_opened = false;
	char		*str;
	char		*temp_str;

	if (is_opened)
	{
		close(p[0]);
		is_opened = false;
	}
	if (pipe(p) == -1)
		return (false);
	is_opened = true;
	while (true)
	{
		rl_on_new_line();
		str = readline(GRAY"> "RESET);
		if (!str || (ft_strcmp(str, end) == 0))
			break ;
		if (ft_strchr(str, '$'))
		{
			temp_str = expand_double_quoted(l, str, envp);
			if (!temp_str)
				return (false);
			free(str);
			str = ft_strdup(temp_str);
			if (!str)
				return (false);
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
