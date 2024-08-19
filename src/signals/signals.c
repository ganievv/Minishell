/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/16 22:43:22 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* handling ctrl-c,
* ignoring ctrl-\,
* crtl-C(is being handled from readine) */
void	handle_sigint_shell(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint_heredoc(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	close(STDIN_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void	change_terminal_echo_ctl(bool turn_off)
{
	struct termios	terminos_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return ;
	if (turn_off)
		terminos_p.c_lflag &= ~(ECHOCTL);
	else
		terminos_p.c_lflag |= ECHOCTL;
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
}
