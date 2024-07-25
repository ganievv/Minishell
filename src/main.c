/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:26 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/25 16:38:18 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	info.envp_buf = envp;
	clear_screen();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		info.input = readline("minishell$ ");
		if (!info.input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(info.input) > 0)
			add_history(info.input);
//		token_list(&tokens, input); /added for testing
		exec_all_cmds(&info);
		free(info.input);
	}
	return (0);
}
