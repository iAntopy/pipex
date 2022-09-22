/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:54:45 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/14 15:04:39 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	if (!s)
		return (NULL);
	cc = (unsigned char)c;
	while (*s && (*s != cc))
		s++;
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}
/*
int	main(int argc, char **argv)
{
	char	*ptr;

	if (argc > 1)
	{
		ptr = ft_strchr(argv[1], *argv[2]);
		ft_printf("Find chr %c in %s : %p\n", *argv[2], argv[1], ptr);//ft_strchr(argv[1], ft_atoi(argv[2])));
		ft_printf("Rest of str at ptr %p : %s\n", ptr, ptr);
	}
	return (0);
}
*/
