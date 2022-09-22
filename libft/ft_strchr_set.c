/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 08:19:40 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/14 15:13:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_set(const char *s, const char *set)
{
	if (!s || !set)
		return (NULL);
	while (*s && !ft_strchr(set, *s))
		s++;
	if (*s)
		return ((char *)s);
	return (NULL);
}
