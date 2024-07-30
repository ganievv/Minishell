/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_export_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:15:19 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 14:17:12 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function prints error message if the given variable
*  name for the 'export' command is not correct			 */
static void	print_err_for_export(char *arg)
{
	write(STDERR_FILENO, "msh: export: `", 14);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier", 25);
}

/* this function checks if the given variable name for the
*  'export' command is correct							*/
int	is_export_arg_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && (arg[i] != '_'))
		return (print_err_for_export(arg), 0);
	i++;
	while ((arg[i] != '=') && arg[i])
	{
		if (!ft_isalnum(arg[i]) && (arg[i] != '_'))
			return (print_err_for_export(arg), 0);
		i++;
	}
	return (1);
}
