/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:53:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/07/21 18:06:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hay, const char *ndl)
{
	char	*h;
	size_t	i;
	size_t	j;

	h = hay;
	if (*ndl == '\0')
		return (h);
	i = -1;
	while (h[++i])
	{
		j = 0;
		while (h[i + j] && ndl[j] && (h[i + j] == ndl[j]))
			j++;
		if (!ndl[j])
			return (h + i);
	}
	return (NULL);
}
/*
int	main(int argc, char *argv[])
{
	char	haystack[] = "Come and get me ! I dare you !\n";
	char	*ret;

	if (argc > 1)
	{
		ft_putstr("Haystack :");
		ft_putstr(haystack);
		ft_putstr("\n");
		ret = ft_strstr(haystack, argv[1]);
		if (ret)
			ft_putstr(ret);
		else
			ft_putstr("ret is NULL\n");
	}
	return (0);
}
*/
