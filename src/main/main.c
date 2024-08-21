/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:26 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/21 17:26:44 by sganiev          ###   ########.fr       */
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

static void	prepare_input(t_msh *info)
{
	signal(SIGINT, handle_sigint_shell);
	change_terminal_echo_ctl(true);
	if (isatty(STDIN_FILENO))
		info->input = readline(GRAY"minishell: "RESET);
	else
		info->input = ft_strtrim(get_next_line(STDIN_FILENO), "\n");
	signal(SIGINT, SIG_IGN);
}

//if (info.cmds)
		//	pipe_group_free(&(info.cmds));
/* we should call the 'change_terminal_echo_ctl(false)'
*  function before exit the shell*/
int	main(int argc, char *argv[], char *envp[])
{
	t_msh		info;
	t_rdr_const	rdr;

	(void)argc;
	(void)argv;
	prog_init(&info, envp);
	while (true)
	{
		rdr.l = info.last_exit_status;
		rdr.envp = info.envp;
		prepare_input(&info);
		if (!info.input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(info.input) > 0)
			add_history(info.input);
		if (!is_input_empty(info.input))
			process_input(&info, rdr);
		free_pids_and_pipes(&info);
	}
	free_rest_vars(&info);
	return (0);
}
