/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:15:26 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/18 21:45:35 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(char *str)
{
	char	*s;

	if (!str)
		return (NULL);
	s = str;
	while (*s)
	{
		if (ft_isupper(*s))
			*s += 32;
		s++;
	}
	return (str);
}
