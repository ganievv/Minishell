/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:53:07 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/25 16:07:42 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_node(char *src, t_env_vars **head)
{
	t_env_vars	*new_node;
	t_env_vars	*current;

	new_node = (t_env_vars *)malloc(sizeof(t_env_vars));
	if (!new_node)
		return (NULL);
	new_node->var = src;
	new_node->next = NULL;
	if (!*head)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	init_env_vars_list(t_msh *info)
{
	int	i;

	i = 0;
	info->env_vars = NULL;
	while (info->envp_buf[i])
		create_node(info->envp_buf[i++], &info->env_vars);
}
