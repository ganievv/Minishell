/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_builtins_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:29:01 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/07 20:02:13 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//function that is swaping
static void	double_array_swap(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	double_array_sort(char **array, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - 1 - i)
			if (ft_strcmp(array[j], array[j + 1]) > 0)
				double_array_swap(&array[j], &array[j + 1]);
	}
}
