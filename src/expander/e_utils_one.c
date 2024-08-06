/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:43 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/06 19:26:12 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_double_quoted_helper_one(t_exp_helper *h, char **envp)
{
	(h->end) = (h->start) + 1;
	while (ft_isalnum(*(h->end)) || *(h->end) == '_')
		(h->end)++;
	h->var = ft_strndup((h->start), (h->end) - (h->start));
	h->temp = h->result;
	h->result = (char *)malloc(ft_strlen(h->result)
			+ ft_strlen(expand_var(h->var, envp)) + 1);
	ft_strcpy(h->result, h->temp);
	ft_strcpy(h->result + ft_strlen(h->temp), expand_var(h->var, envp));
	free(h->temp);
	free(h->var);
	(h->start) = (h->end);
}

char	*expand_double_quoted(char *input, char **envp)
{
	t_exp_helper	h;

	h.result = ft_strdup("");
	(h.start) = input;
	while (*(h.start))
	{
		if (*(h.start) == '$')
			expand_double_quoted_helper_one(&h, envp);
		else
		{
			h.temp = h.result;
			h.len = ft_strlen(h.result) + 2;
			h.result = (char *)malloc(h.len);
			ft_strcpy(h.result, h.temp);
			h.result[h.len - 2] = *(h.start);
			h.result[h.len - 1] = '\0';
			free(h.temp);
			(h.start)++;
		}
	}
	return (ft_strtrim(h.result, "\""));
}
