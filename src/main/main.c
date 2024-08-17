/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:26 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/17 15:10:25 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prog_init(t_msh *info, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	t_msh_init(info, envp);
	change_or_add_env_var("OLDPWD", &info->envp);
	handle_shlvl_var(info);
	clear_screen();
	print_header();
}

/* we should call the 'change_terminal_echo_ctl(false)'
*  function before exit the shell*/
int	main(int argc, char *argv[], char *envp[])
{
	t_msh		info;
	t_token		*ready;
	t_rdr_const rdr;

	(void)argc;
	(void)argv;
	prog_init(&info, envp);
	rdr.l = info.last_exit_status;
	rdr.envp = info.envp;
	while (true)
	{
		signal(SIGINT, handle_sigint_shell);
		change_terminal_echo_ctl(true);
		ready = NULL;
		if (isatty(fileno(stdin)))
			info.input = readline(GRAY"minishell: "RESET);
		else
			info.input = ft_strtrim(get_next_line(fileno(stdin)), "\n");
		signal(SIGINT, SIG_IGN);
		if (!info.input)
			return (printf("exit\n"), 0);
		if (ft_strlen(info.input) > 0)
			add_history(info.input);
		if (!is_input_empty(info.input))
		{
			tokenize(info.input, &(info.tokens));
			token_ready_for_parsing(info.last_exit_status, info.tokens,
				&ready, envp);
			token_free(&(info.tokens));
			info.tokens = ready;
			info.cmds = parse_pipeline(rdr, &(info.tokens));
			exec_all_cmds(&info);
		}
		free_all_prog_vars(&info);
	}
	change_terminal_echo_ctl(false);
	free_arr_str(info.envp);
	rl_clear_history();
	return (0);
}
