/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:41:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/15 20:11:15 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	void	*ptr;
	size_t	mem_size;

	if (!n || !s)
		return (ft_calloc(1, 1));
	if (s > (SIZE_MAX / n))
		return (NULL);
	mem_size = n * s;
	ptr = malloc(mem_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, mem_size);
	return (ptr);
}
