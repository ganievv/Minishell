/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_executor_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:49:23 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/12 18:29:37 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*str_to_lower_case(const char *cmd)
{
	char	*cmd_cp;
	int		i;

	i = -1;
	cmd_cp = ft_strdup(cmd);
	while (cmd_cp && cmd_cp[++i])
		cmd_cp[i] = ft_tolower(cmd_cp[i]);
	return (cmd_cp);
}

void	print_cmd_not_found(char *cmd)
{
	write(STDERR_FILENO, "msh: ", 5);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 20);
}
