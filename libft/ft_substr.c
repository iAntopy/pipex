/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:54:31 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 16:38:21 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_empty_str(void)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	return (ptr);
}

char	*ft_substr(char const *str, unsigned int start, size_t n)
{
	char	*dup;
	char	*d;
	size_t	str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if ((start > str_len) || (n == 0))
		return (return_empty_str());
	str_len -= start;
	str += start;
	if (n < str_len)
		str_len = n;
	dup = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!dup)
		return (NULL);
	d = dup;
	while (str_len--)
		*(d++) = *(str++);
	*d = '\0';
	return (dup);
}
