/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:54:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/21 23:03:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	if (!s)
		return (NULL);
	cc = (unsigned char)c;
	while (*s && (*s != cc))
		s++;
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}
