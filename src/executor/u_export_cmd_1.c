/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_export_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:15:19 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/10 23:01:57 by sganiev          ###   ########.fr       */
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
	write(STDERR_FILENO, "\n", 1);
}

/* this function checks if the given variable
*  name for the 'export' command is correct */
int	is_export_arg_valid(char *arg)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && (arg[i] != '_'))
		return (print_err_for_export(arg), 0);
	i++;
	while (arg[i] && (arg[i] != '='))
	{
		if (!ft_isalnum(arg[i]) && (arg[i] != '_'))
			return (print_err_for_export(arg), 0);
		i++;
	}
	return (1);
}

static void	form_output_str(char *name, char *value)
{
	if (name)
	{
		write (STDOUT_FILENO, "declare -x ", 11);
		write (STDOUT_FILENO, name, ft_strlen(name));
		if (value)
		{
			write (STDOUT_FILENO, "=\"", 2);
			write (STDOUT_FILENO, value, ft_strlen(value));
			write (STDOUT_FILENO, "\"", 1);
		}
		write (STDOUT_FILENO, "\n", 1);
	}
}

/* this function prints all environment
*  variables for the 'export' command*/
void	print_env_vars(char **list)
{
	char	**sorted;
	char	*name;
	char	*value;
	int		i;

	i = -1;
	sorted = copy_arr_str(list);
	if (!sorted)
		return ;
	double_array_sort(sorted, count_args(sorted));
	while (sorted[++i])
	{
		name = take_env_var_name(sorted[i]);
		value = take_env_var_value(sorted[i]);
		form_output_str(name, value);
		if (name)
			free(name);
		if (value)
			free(value);
	}
	free_arr_str(sorted);
}
