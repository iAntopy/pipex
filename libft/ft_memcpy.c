/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:49:29 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/21 18:11:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			*dp;
	size_t			*sp;
	unsigned char	*dpc;
	unsigned char	*spc;

	dp = (size_t *)dest;
	sp = (size_t *)src;
	while (n >= sizeof(size_t))
	{
		*(dp++) = *(sp++);
		n -= sizeof(size_t);
	}
	if (n)
	{
		dpc = (unsigned char *)dp;
		spc = (unsigned char *)sp;
		while (n--)
			*(dpc++) = *(spc++);
	}
	return (dest);
}
