/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:59:38 by tnakas            #+#    #+#             */
/*   Updated: 2024/07/22 21:02:47 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_nbr(char *arg)
{
	if (!arg)
		return (0);
	while (ft_isspace(*arg))
		arg++;
	if ((*arg == '+') || (*arg == '-'))
		arg++;
	if (*arg == '\0')
		return (0);
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

long long	ft_atoll(char *str)
{
	//test;
}

int	is_valid_exit_range(char *nbr)
{
// protected
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
