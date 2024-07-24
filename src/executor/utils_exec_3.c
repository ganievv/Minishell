/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:53:07 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/24 22:41:48 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_name_and_value(char *src, t_env_vars *var)
{
	char	*ptr;

	var->var.name = src;
	ptr = ft_strchr(src, '=');
	var->var.value = ptr + 1;
	*ptr = '\0';
}

static void	create_node(char *src, t_env_vars **head)
{
	t_env_vars	*new_node;
	t_env_vars	*current;

	new_node = (t_env_vars *)malloc(sizeof(t_env_vars));
	if (!new_node)
		return (NULL);
	set_name_and_value(src, new_node);
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
