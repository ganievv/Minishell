/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:43 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/07 17:58:49 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	expand_double_quoted_helper_one(int l, t_exp_helper *h, char **envp)
{
	(h->end) = (h->start) + 1;
	while (ft_isalnum(*(h->end)) || *(h->end) == '_' || *(h->end) == '?')
		(h->end)++;
	h->var = ft_strndup((h->start), (h->end) - (h->start));
	if (!h->var)
		return ;
	h->temp = h->result;
	h->result = (char *)malloc(ft_strlen(h->result)
			+ ft_strlen(expand_var(l, h->var, envp)) + 1);
	if (!h->result)
		return ;
	ft_strcpy(h->result, h->temp);
	ft_strcpy(h->result + ft_strlen(h->temp), expand_var(l, h->var, envp));
	free(h->temp);
	free(h->var);
	(h->start) = (h->end);
}

static void	expand_double_quoted_helper_two(t_exp_helper *h)
{
	h->temp = h->result;
	h->len = ft_strlen(h->result) + 2;
	h->result = (char *)malloc(h->len);
	if (!h->result)
		return ;
	ft_strcpy(h->result, h->temp);
	h->result[h->len - 2] = *(h->start);
	h->result[h->len - 1] = '\0';
	free(h->temp);
	(h->start)++;
}

char	*expand_double_quoted(int l, char *input, char **envp)
{
	t_exp_helper	h;
	char			*temp;

	h.result = ft_strdup("");
	if (!h.result)
		return NULL;
	(h.start) = input;
	while (*(h.start))
	{
		if (*(h.start) == '$')
			expand_double_quoted_helper_one(l, &h, envp);
		else
			expand_double_quoted_helper_two(&h);
	}
	temp = ft_strtrim(h.result, "\"\'");
	if (!temp)
	{
		free(h.result);
		return (NULL);
	}
	free(h.result);
	return (temp);
}
