/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:26 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/09 15:11:21 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prog_init(t_msh *info, char **envp)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	info->envp = envp;
	info->last_exit_status = 0;
	clear_screen();
	print_header();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_msh	info;

	(void)argc;
	(void)argv;
	prog_init(&info, envp);
	while (1)
	{
		info.input = readline("\x1b[90mminishell$ \x1b[0m");
		if (!info.input)
			return (printf("exit\n"), 0);
		if (ft_strlen(info.input) > 0)
			add_history(info.input);
		if (!is_input_empty(info.input))
		{
			t_token *head = NULL;
			tokenize(info.input, &head);
			info.cmds = parse_pipeline(&head);
			expand_parsed_commands(info.last_exit_status, info.cmds, envp);
			exec_all_cmds(&info);
			pipe_group_free(&(info.cmds));
			token_free(&head);
		}
		free(info.input);
	}
	return (0);
}
