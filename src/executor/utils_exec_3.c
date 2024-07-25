/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:53:07 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/25 18:41:26 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cmp(char *var, char *data)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (ft_strncmp(var, data, i));
}

void	remove_env_var(t_env_vars **head, char *data)
{
	t_env_vars	*cur;
	t_env_vars	*next;
	t_env_vars	*prev;

	if (head == NULL || *head == NULL)
		return ;
	cur = *head;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		if (cmp(cur->var, data) == 0)
		{
			if (prev == NULL)
				*head = next;
			else
				prev->next = next;
			free(cur);
		}
		else
			prev = cur;
		cur = next;
	}
}

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
