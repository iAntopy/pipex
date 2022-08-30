/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:53:26 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/29 02:10:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mstr;
	unsigned int	len;
	unsigned int	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!malloc_free_p(sizeof(char) * (len + 1), (void **)&mstr))
		return (NULL);
	i = -1;
	while (++i < len)
		mstr[i] = f(i, s[i]);
	mstr[i] = '\0';
	return (mstr);
}
