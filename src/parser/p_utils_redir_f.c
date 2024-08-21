/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_redir_f.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:35:49 by sganiev           #+#    #+#             */
/*   Updated: 2024/08/21 14:31:26 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_new_file_node(t_redir_files **node)
{
	if (!node || !*node)
		return ;
	free_str(&((*node)->file));
	free(*node);
	*node = NULL;
}

void	redir_files_lstadd(t_redir_files **head, t_redir_files *new_file)
{
	t_redir_files	*temp;

	if (!head)
		return (free_new_file_node(&new_file));
	temp = *head;
	if (!temp)
		*head = new_file;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_file;
	}
}

t_redir_files	*create_redir_file(char *file, int mode, int redir_type)
{
	t_redir_files	*new_token;

	new_token = (t_redir_files *)malloc(sizeof(t_redir_files));
	if (!new_token)
		return (free_str(&file), NULL);
	new_token->file = file;
	new_token->mode = mode;
	new_token->redir_type = redir_type;
	new_token->next = NULL;
	return (new_token);
}

void	free_t_redir_files(t_redir_files **head)
{
	t_redir_files	*tmp;
	t_redir_files	*next;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free_str(&(tmp->file));
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}
