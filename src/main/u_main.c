/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:58:50 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/10 20:16:40 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	t_msh_init(t_msh *info, char **envp)
{
	info->input = NULL;
	info->tokens = NULL;
	info->cmds = NULL;
	info->pids = NULL;
	info->pipes = NULL;
	info->last_exit_status = 0;
	info->envp = copy_arr_str(envp);
	init_builtin_names(info->builtin_names);
	init_builtin_ptrs(info->builtin_ptrs);
}

/* clear screen before prompt */
void	clear_screen(void)
{
	printf("\033[H\033[J");
}

int	is_input_empty(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (0);
		input++;
	}
	return (1);
}

void	free_all_prog_vars(t_msh *info)
{
	pipe_group_free(&(info->cmds));
	token_free(&(info->tokens));
	if (info->input)
	{
		free(info->input);
		info->input = NULL;
	}
	free_pids_and_pipes(info);
}

static void	add_to_shlvl(t_msh *info, int var_i)
{
	char	*old_value;
	char	*new_value;
	char	*tmp;
	int		nbr;

	old_value = take_env_var_value(info->envp[var_i]);
	if (old_value)
	{
		if ((ft_strlen(old_value) < 4) && is_nbr(old_value))
		{
			nbr = ft_atoi(old_value);
			if (nbr >= 0)
			{
				new_value = ft_itoa(nbr + 1);
				tmp = new_value;
				new_value = ft_strjoin("SHLVL=", new_value);
				change_or_add_env_var(new_value, &info->envp);
				return (free(tmp), free(new_value), (void)0);
			}
			change_or_add_env_var("SHLVL=0", &info->envp);
			return (free(old_value), (void)0);
		}
		free(old_value);
	}
	change_or_add_env_var("SHLVL=1", &info->envp);
}

void	handle_shlvl_var(t_msh *info)
{
	int		var_i;

	var_i = search_env_var("SHLVL", info->envp);
	if (var_i == -1)
		change_or_add_env_var("SHLVL=1", &info->envp);
	else
		add_to_shlvl(info, var_i);
}
