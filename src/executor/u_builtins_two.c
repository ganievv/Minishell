/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_builtins_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:29:01 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/07 19:59:19 by tnakas           ###   ########.fr       */
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
		while (++j < size - 1 - i )
			if (ft_strcmp(array[j], array[j + 1]) > 0)
				double_array_swap(&array[j], &array[j + 1]);
	}
}

//function that is sorting

// int main()
// {
//     // Sample array of strings
//     char *strings[] = {
//         "banana",
//         "apple",
//         "grape",
//         "cherry",
//         "mango",
//         NULL // Ensure the array ends with NULL
//     };

//     // Calculate the size of the array
//     int size = 0;
//     while (strings[size] != NULL)
//     {
//         size++;
//     }

//     // Print before sorting
//     printf("Before sorting:\n");
//     for (int i = 0; i < size; i++)
//     {
//         printf("%s\n", strings[i]);
//     }

//     // Sort the array
//     double_array_sort(strings, size);

//     // Print after sorting
//     printf("\nAfter sorting:\n");
//     for (int i = 0; i < size; i++)
//     {
//         printf("%s\n", strings[i]);
//     }

//     return 0;
// }