/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:49:29 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 14:41:30 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dc;
	unsigned char	*sc;

	if (!dest && !src)
		return (NULL);
	dc = (unsigned char *)dest;
	sc = (unsigned char *)src;
	while (n--)
		*(dc++) = *(sc++);
	return (dest);
}
