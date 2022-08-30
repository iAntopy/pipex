/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:00:46 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 14:44:20 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	cc;

	ptr = NULL;
	cc = (unsigned char)c;
	while (*s)
	{
		if (*s == cc)
			ptr = (char *)s;
		s++;
	}
	if (*s == cc)
		ptr = (char *)s;
	return (ptr);
}
