/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:26 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/10 17:04:19 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prog_init(t_msh *info, char **envp)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	t_msh_init(info, envp);
	change_or_add_env_var("OLDPWD", &info->envp);
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
			tokenize(info.input, &(info.tokens));
			info.cmds = parse_pipeline(&(info.tokens));
			expand_parsed_commands(info.last_exit_status, info.cmds, envp);
			exec_all_cmds(&info);
		}
		free_all_prog_vars(&info);
	}
	free_arr_str(info.envp);
	rl_clear_history();
	return (0);
}
