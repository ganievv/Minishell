/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_export_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:45:27 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 18:12:12 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	rest_copy(char **dst, char **src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = NULL;
}

static void	add_var(char *var, char ***envp)
{
	char	**copy;
	int		len;

	len = count_args(*envp) + 2;
	copy = (char **)malloc(sizeof(char *) * len);
	if (!copy)
		return (copy);
	copy[0] = ft_strdup(var);
	rest_copy(copy + 1, *envp);
	free(*envp);
	*envp = copy;
}

static void	change_var_value(char *var, int var_i, char ***envp)
{
	free(*envp[var_i]);
	*envp[var_i] = ft_strdup(var);
}

void	change_or_add_env_var(char *var, char ***envp)
{
	char	*new_envp;
	int		var_i;

	var_i = search_env_var(var, *envp);
	if (var_i != -1)
		change_var_value(var, var_i, envp);
	else
		add_var(var, envp);
}
