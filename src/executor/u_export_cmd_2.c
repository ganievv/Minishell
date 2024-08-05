/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_export_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:45:27 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/05 17:59:49 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* this function copies addresses of environment
*  variables to their new positions in the array*/
static void	rest_copy(char **dst, char **src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = NULL;
}

/* this function creates a new array from the 'envp'
*  list of environment variables and adds the new
*  variable at the first position */
static void	add_var(char *var, char ***envp)
{
	char	**copy;
	int		len;

	len = count_args(*envp) + 2;
	copy = (char **)malloc(sizeof(char *) * len);
	if (!copy)
		return ;
	copy[0] = ft_strdup(var);
	rest_copy(copy + 1, *envp);
	free(*envp);
	*envp = copy;
}

/* this function frees the old value of the variable 'var'
*  at the 'var_i' index in the 'envp' array and copies
*  a new value to this position in the 'envp' array		*/
static void	change_var_value(char *var, int var_i, char ***envp)
{
	free((*envp)[var_i]);
	(*envp)[var_i] = ft_strdup(var);
}

/* this function searches for the 'var' environment
*  variable in the 'envp' array of strings:
*
*  - if the variable is found, it invokes a function 
*	 to replace the current value with the new value;
*
*  - if the variable is not found, it invokes a function
*	 to add the variable to the string array		  */
void	change_or_add_env_var(char *var, char ***envp)
{
	int	var_i;

	var_i = search_env_var(var, *envp);
	if (var_i != -1)
		change_var_value(var, var_i, envp);
	else
		add_var(var, envp);
}
