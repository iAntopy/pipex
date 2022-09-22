/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:16:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/21 18:34:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	malloc_free_p(size_t size, void **ptr)
{	
	if (size)
	{
		if (!ptr)
			return (0);
		*ptr = malloc(size);
		return (*ptr != NULL);
	}
	else if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (1);
}

void	*malloc_free(size_t size, void **ptr)
{	
	if (size)
	{
		*ptr = malloc(size);
		if (*ptr)
			return (*ptr);
	}
	else if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
