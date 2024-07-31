/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:49:23 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/31 19:53:52 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**skip_all_flags(char **args)
{
	int	i;

	if (!args)
		return (args);
	while (*args)
	{
		if (*args[0] == '-')
			args++;
		else
			break ;
	}
	return (args);
}
