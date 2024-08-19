/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:43 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 23:08:35 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	copy_and_free(char **result, char *temp,
				char *expanded_var, char *var)
{
	if (!(*result))
	{
		free(temp);
		temp = NULL;
		free(var);
		var = NULL;
		return ;
	}
	ft_strcpy(*result, temp);
	ft_strcpy(*result + ft_strlen(temp), expanded_var);
	free(temp);
	temp = NULL;
	free(var);
	var = NULL;
	free(expanded_var);
	expanded_var = NULL;
}

static void	expand_double_quoted_helper_one(int l, t_exp_helper *h, char **envp)
{
	char	*expanded_var;

	h->end = h->start + 1;
	while (ft_isalnum(*(h->end)) || *(h->end) == '_' || *(h->end) == '?')
	{
		if (*(h->end) == '?')
		{
			h->end++;
			break ;
		}
		h->end++;
	}
	h->var = ft_strndup(h->start, h->end - h->start);
	if (!h->var)
		return ;
	h->temp = h->result;
	expanded_var = expand_var(l, h->var, envp);
	h->result = (char *)malloc(ft_strlen(h->temp)
			+ ft_strlen(expanded_var) + 1);
	copy_and_free(&(h->result), h->temp, expanded_var, h->var);
	h->start = h->end;
}

static void	expand_double_quoted_helper_two(t_exp_helper *h)
{
	h->temp = h->result;
	h->len = ft_strlen(h->result) + 2;
	h->result = (char *)malloc(h->len);
	if (!h->result)
	{
		free(h->temp);
		h->temp = NULL;
		free(h->var);
		h->var = NULL;
		return ;
	}
	ft_strcpy(h->result, h->temp);
	h->result[h->len - 2] = *(h->start);
	h->result[h->len - 1] = '\0';
	free(h->temp);
	(h->start)++;
}

char	*expand_double_quoted(int l, char *input, char **envp)
{
	t_exp_helper	h;

	h.result = ft_strdup("");
	if (!h.result)
		return (NULL);
	(h.start) = input;
	while (*(h.start))
	{
		if (*(h.start) == '$')
			expand_double_quoted_helper_one(l, &h, envp);
		else
			expand_double_quoted_helper_two(&h);
	}
	return (h.result);
}
