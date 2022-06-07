/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:55:35 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 16:27:00 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		dst_len;
	size_t		n;
	char		*d;
	const char	*s;

	n = size;
	d = dest;
	while (n-- && *d)
		d++;
	dst_len = d - dest;
	n = size - dst_len;
	if (!n)
		return (dst_len + ft_strlen(src));
	s = src;
	while (*s && --n)
		*(d++) = *(s++);
	*d = '\0';
	while (*s)
		s++;
	return (dst_len + (s - src));
}
