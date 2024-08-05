/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:53:07 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/05 15:22:00 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function returns an allocated
*  string containing the value of the
*  environment variable			   */
char	*take_env_var_value(char *var)
{
	char	*begin;
	char	*value;

	value = NULL;
	begin = ft_strchr(var, '=');
	if (begin)
		value = ft_strdup(begin + 1);
	return (value);
}

/* this function returns an allocated
*  string containing the name  of the
*  environment variable			   */
char	*take_env_var_name(char *var)
{
	char	*end;
	char	*name;

	name = NULL;
	end = ft_strchr(var, '=');
	if (end)
		name = ft_strndup(var, end - var);
	else
		name = ft_strdup(var);
	return (name);
}

/* this function compares names of environment variables
*  up to the '=' or '\0' character
*
*  return values:
*				  '0' 	  - variables names are the same
*				  'not 0' - variables names are NOT the same */
static int	cmp_env_vars_names(char *var, char *data)
{
	int	i;

	i = 0;
	while (var[i] && (var[i] != '='))
		i++;
	return (ft_strncmp(var, data, i));
}

/* this function search certain environment variable
*  in the list of all environment variables;
*
*  return values:
*				  1) index of environment var in the 'envp'
*				  2) '-1': if there is no such variable */
int	search_env_var(char *var_to_find, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (cmp_env_vars_names(envp[i], var_to_find) == 0)
			return (i);
	}
	return (-1);
}
