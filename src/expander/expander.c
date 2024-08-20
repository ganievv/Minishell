/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:45 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/20 18:27:37 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_var(int l, char *input, char **envp)
{
	int		i;
	char	*var_name;

	if (*input != '$')
		return (ft_strdup(input));
	if (*(input + 1) == '?' || (ft_isspace(*(input + 1))
			|| *(input + 1) == '\0'))
	{
		if (ft_isspace(*(input + 1)) || *(input + 1) == '\0')
			return (ft_strdup("$"));
		return (ft_itoa(l));
	}
	var_name = input + 1;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0
			&& envp[i][ft_strlen(var_name)] == '=')
			return (ft_strdup(envp[i] + ft_strlen(var_name) + 1));
	}
	return (ft_strdup(""));
}

static void	ex_par_com_h_one(char **src, char *dest)
{
	if (!dest)
		return ;
	if (dest)
	{
		free(*src);
		*src = dest;
	}
}

void	expand_parsed_commands(int l, t_pipe_group *group, char **envp)
{
	int		i;
	char	*ex_cont;

	ex_cont = NULL;
	while (group)
	{
		i = -1;
		while (group->args && group->args[++i])
		{
			if (group->args[i][0] == '$')
				ex_cont = expand_var(l, group->args[i], envp);
			else if (group->args[i][0] == '\"')
				ex_cont = expand_double_quoted(l, group->args[i], envp);
			else if (group->args[i][0] == '\'')
				ex_cont = ft_strtrim(group->args[i], "\'");
			else
				ex_cont = expand_unquoted(l, group->args[i], envp);
			ex_par_com_h_one(&(group->args[i]), ex_cont);
		}
		group = group->next;
	}
}

char	*expand_unquoted(int l, char *input, char **envp)
{
	return (expand_var(l, input, envp));
}
