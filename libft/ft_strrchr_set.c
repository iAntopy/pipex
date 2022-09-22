/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 07:30:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/19 20:12:04 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr_set(const char *s, const char *set)
{
	char	*p;

	if (!s || !set)
		return (NULL);
	p = (char *)s + ft_strlen(s);
	while (--p >= s)
		if (ft_strrchr(set, *p))
			return (p);
	return (NULL);
}
