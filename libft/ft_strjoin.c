/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:55:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 15:00:25 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jstr;
	char	*j;

	if (!s1 || !s2)
		return (NULL);
	jstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!jstr)
		return (NULL);
	j = jstr;
	while (*s1)
		*(j++) = *(s1++);
	while (*s2)
		*(j++) = *(s2++);
	*j = '\0';
	return (jstr);
}
