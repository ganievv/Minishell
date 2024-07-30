/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:53:07 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 17:43:42 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function removes a certain environment variable named 
*  'data' from the linked list of them (info->env_vars)		*/
void	remove_env_var()
{
}

/* this function compares names of environment variables
*  up to the '=' sign (which indicates the end of the name)
*
*  return values:
*				  '0' 	  - variables names are the same
*				  'not 0' - variables names are NOT the same */
static int	cmp_env_vars_names(char *var, char *data)
{
	int	i;

	i = 0;
	while (var[i] != '=')
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
