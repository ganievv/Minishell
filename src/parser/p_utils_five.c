/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sganiev <sganiev@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 05:20:30 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/21 03:37:45 by sganiev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_args(t_token **tokens, t_pipe_group *group)
{
	t_token	*temp;
	char	*current_str;
	char	**args;
	int		i;

	temp = *tokens;
	current_str = NULL;
	args = NULL;
	i = 0;
	while (temp && temp->type == SPC)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		while (temp && (p_command_h_one(temp) || p_redir_h_one(temp)))
		{
			p_args_skip_spaces(&temp);
			join_command_str(&temp, &current_str);
			add_arg_and_skip_spaces(&args, current_str, &temp, &i);
		}
	}
	group->args = args;
	(*tokens) = temp;
}

char	**args_join(char **src, char *new_arg)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (count_args(src) + 2));
	if (!res)
		return (free_arr_str(&src), NULL);
	while (src && src[i])
	{
		res[i] = ft_strdup(src[i]);
		if (!res[i])
			return (free_arr_str(&res), NULL);
		i++;
	}
	res[i] = new_arg;
	res[i + 1] = NULL;
	if (src != NULL)
		free_arr_str(&src);
	return (res);
}
