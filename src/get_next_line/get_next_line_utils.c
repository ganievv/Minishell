/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:13:34 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/14 18:23:45 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_substr_get(char *s, int start, int length)
{
	char		*res;
	int			i;

	i = ft_strlen_get(s);
	if (start > i)
		length = 0;
	if (length > i - start)
		length = i - start;
	res = (char *)malloc(length + 1);
	if (!res)
		return (free(res), free(s), NULL);
	i = -1;
	while (++i < length)
		*(res + i) = *(s + start + i);
	*(res + i) = '\0';
	return (res);
}

char	*ft_strjoin_get(char *s1, char *s2, int len)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(len + 1);
	if (!res)
		return (free(res), free(s1), free(s2), NULL);
	i = -1;
	j = -1;
	while (*(s1 + (++i)))
		res[i] = s1[i];
	while (*(s2 + (++j)))
		*(res + i + j) = *(s2 + j);
	*(res + i + j) = '\0';
	return (free(s1), res);
}

int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	while (*(str + i) && *(str + i) != '\n')
		i++;
	if (*(str + i) == '\n')
		i++;
	return (i);
}

int	ft_str_bs(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (*(str + (++i)))
	{
		if (*(str + i) == c)
			return (i);
	}
	if (*(str + i) == c)
		return (i);
	return (-1000);
}

int	ft_strlen_get(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}
