/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakas <tnakas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:06:05 by tnakas            #+#    #+#             */
/*   Updated: 2024/08/19 15:43:15 by tnakas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		ft_free(ptr, old_size);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		return (NULL);
	}
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, new_size);
		free(ptr);
		ptr = NULL;
	}
	return (new_ptr);
}
