/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:53:07 by sganiev           #+#    #+#             */
/*   Updated: 2024/07/27 18:02:41 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/* this function removes a certain environment variable named 
*  'data' from the linked list of them (info->env_vars)		*/
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

/* this function creates new node for the linked list of environment
*  variables (info->env_vars) and assign to it certain value (src) */
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

/* this function convert environment variables array from 'char**'
*  (info->envp_buf) to the linked list of them (info->env_vars)		*/
void	init_env_vars_list(t_msh *info)
{
	int	i;

	i = 0;
	info->env_vars = NULL;
	while (info->envp_buf[i])
		create_node(info->envp_buf[i++], &info->env_vars);
}

/* this function search certain environment variable in the linked
*  list of all environment variables (info->env_vars);
*
*  return values:
*				  1) environment var (char *)
*				  2) NULL - if there is no such variable		  */
char	*search_env_var(t_env_vars *env_vars, char *var_to_find)
{
	while (env_vars)
	{
		if (cmp_env_vars_names(env_vars->var, var_to_find) == 0)
			return (env_vars->var);
		env_vars = env_vars->next;
	}
	return (NULL);
}
