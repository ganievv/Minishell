/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_unset_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:30:34 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 20:31:54 by sganiev          ###   ########.fr       */
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
