/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_main_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:24:23 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/19 06:40:19 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all_prog_vars(t_msh *info)
{
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
				return (free(tmp), free(new_value), free(old_value), (void)0);
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
