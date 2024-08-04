/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:49:43 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/04 21:21:56 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	var_d_quoted_exp_h_init(char *input, t_exp_helper *h)
{
	h->res = NULL;
	h->var_name = NULL;
	h->exp_var = NULL;
	h->temp = NULL;
	h->start = input;
	(h->end) = NULL;
}

static void	var_d_quoted_exp_h_one(t_exp_helper *h, char **envp)
{
	(h->end) = h->start + 1;
	while (*(h->end) && (ft_isalnum(*(h->end)) || *(h->end) == '_'))
		(h->end)++;
	h->var_name = strndup(h->start, (h->end) - h->start);
	h->exp_var = var_exp(h->var_name, envp);
	h->temp = h->res;
	h->res = (char *)malloc(strlen(h->temp) + ft_strlen(h->exp_var) + 1);
	if (!h->res)
		return (NULL);
	ft_strcpy(h->res, h->temp);
	ft_strcpy(h->res + ft_strlen(h->temp), h->exp_var);
	free(h->temp);
	free(h->var_name);
	free(h->exp_var);
	h->start = (h->end);
}

char	*var_d_quoted_exp(char *input, char **envp)
{
	t_exp_helper	h;

	var_d_quoted_exp_h_init(input, &h);
	while (h.start)
	{
		if (*h.start == '$')
			var_d_quoted_exp_h_one(&h, envp);
		else
		{
			h.temp = h.res;
			h.res = (char *)malloc(ft_strlen(h.temp) + 2);
			ft_strcpy(h.res, h.temp);
			h.res[ft_strlen(h.temp) + 1] = h.start[0];
			free(h.temp);
			h.start++;
		}
	}
	return (h.res);
}
