/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:26 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/07 13:54:53 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_input_empty(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (0);
		input++;
	}
	return (1);
}

/* clear screen before prompt */
static void	clear_screen(void)
{
	printf("\033[H\033[J");
}

/* handling ctrl-c,
* ignoring ctrl-\,
* crtl-C(is being handled from readine) */
void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_msh		info;
//	t_data		data; /added for testing
//    t_token		*tokens = NULL; /added for testing

//	tokens = NULL; /added for testing
	(void)argc;
	(void)argv;
	info.envp = envp;
	info.last_exit_status = 0;
	clear_screen();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	print_header();
	while (1)
	{
		info.input = readline("\x1b[90mminishell$ \x1b[0m");
		if (!info.input)
		{
			printf("exit\n");
			break ;
		}
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
