/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_echo_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:21:19 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/09 17:52:25 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_correct_flag(char flag, char *arg)
{
	int	i;

	if (!arg)
		return (false);
	i = 0;
	if (arg[i++] != '-')
		return (false);
	if (arg[i++] != flag)
		return (false);
	while (arg[i] && (arg[i] != ' '))
	{
		if (arg[i++] != flag)
			return (false);
	}
	return (true);
}

bool	check_cmd_flag(char flag, char ***args)
{
	char	**tmp;
	int		i;
	int		to_skip;

	if (!args || !*args || !**args)
		return (false);
	i = 0;
	to_skip = 0;
	tmp = *args;
	if (!is_correct_flag(flag, tmp[i++]))
		return (false);
	to_skip++;
	while (tmp[i])
	{
		if (!is_correct_flag(flag, tmp[i++]))
			break;
		to_skip++;
	}
	*args += to_skip;
	return (true);
}
