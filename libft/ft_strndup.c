/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:53:03 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/28 05:36:17 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*dup;
	char	*d;
	size_t	str_len;

	if (!str || !n)
		return (NULL);
	str_len = ft_strlen(str);
	if (n < str_len)
		str_len = n;
	if (!malloc_free_p(sizeof(char) * (str_len + 1), (void **)&dup))
		return (NULL);
	d = dup;
	while (str_len--)
		*(d++) = *(str++);
	*d = '\0';
	return (dup);
}
