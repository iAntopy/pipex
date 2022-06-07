/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:50:29 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/01 19:35:18 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_bwrd_cpy(unsigned char *dest, unsigned char *src, size_t n)
{
	while (n--)
		dest[n] = src[n];
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if ((src < dest) && (dest < (src + n)))
		ft_bwrd_cpy((unsigned char *)dest, (unsigned char *)src, n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
