/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfltr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:28:10 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/12 18:03:16 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static is char on char set
static int	is_char_on_charset(char c, char *char_set)
{
	if (ft_strchr(char_set, (int)c))
		return (1);
	return (0);
}

static size_t	ft_strnewlen(char *src, char *char_set)
{
	int	i;
	int	new_len;

	i = -1;
	new_len = 0;
	while (src[++i])
	{
		if (is_char_on_charset(src[i], char_set))
			continue ;
		new_len++;
	}
	return (new_len);
}

void	ft_strfltr(char **src, char *char_set)
{
	char	*temp;
	int		i;
	int		j;

	temp = (char *)malloc(sizeof(char) * (ft_strnewlen(*src, char_set) + 1));
	if (!temp)
		return ;
	i = -1;
	j = -1;
	while ((*src)[++j])
		if (!is_char_on_charset((*src)[j], char_set))
			temp[++i] = (*src)[j];
	temp[i + 1] = '\0';
	free(*src);
	*src = temp;
}

// int	main(int argc, char **argv)
// {
// 	char	*test;

// 	test = NULL;
// 	if (argc == 2)
// 	{
// 		test = ft_strdup(argv[1]);
// 		ft_strfltr(&test, "\"\'\\&^");
// 		ft_putstr_fd(test, 1);
// 		ft_putstr_fd("\n", 1);
// 	}
// 	return (0);
// }