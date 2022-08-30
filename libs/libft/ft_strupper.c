/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 21:19:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/18 21:46:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupper(char *str)
{
	char	*s;

	if (!str)
		return (NULL);
	s = str;
	while (*s)
	{
		if (ft_islower(*s))
			*s -= 32;
		s++;
	}
	return (str);
}
