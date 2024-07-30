/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_cd_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:06:01 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/30 20:17:13 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd_var(char ***envp)
{
	char	buff[PATH_MAX];
	char	*buff_ptr;
	int		var_i;
	char	*new_path;

	buff_ptr = getcwd(buff, sizeof(buff));
	if (buff_ptr)
	{
		new_path = ft_strjoin("PWD=", buff);
		if (!new_path)
			return ;
		var_i = search_env_var("PWD", *envp);
		if (var_i != -1)
		{
			free(*envp[var_i]);
			*envp[var_i] = new_path;
		}
		else
			free(new_path);
	}
}
