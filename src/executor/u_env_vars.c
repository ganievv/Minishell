/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:53:07 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 19:50:04 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function copies pointers to strings from the
*  'src' array to the 'dst' array; it skips the string
*  in 'src' at the index 'var_i'*/
static void	rest_copy(int var_i, char **dst, char **src)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (y != var_i)
		dst[i++] = src[y++];
	if (y == var_i)
		y++;
	while (src[y])
		dst[i++] = src[y++];
	dst[i] = NULL;
}

/* this function removes a certain environment 
*  variable named 'var' from the array 'envp'*/
void	remove_env_var(char *var, char ***envp)
{
	char	**envp_new;
	int		var_i;
	int		len;

	var_i = search_env_var(var, *envp);
	if (var_i != -1)
	{
		len = count_args(*envp) + 2;
		envp_new = (char **)malloc(sizeof(char *) * len);
		if (envp_new)
		{
			rest_copy(var_i, envp_new, *envp);
			free(*envp);
			*envp = envp_new;
		}
	}
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
