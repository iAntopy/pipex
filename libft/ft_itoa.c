/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:45:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/28 05:44:19 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_log10(int n)
{
	int	o;

	o = 0;
	while (n)
	{
		n /= 10;
		o++;
	}
	return (o);
}

static void	ft_writenbr(char *nstr, long long int nb)
{
	while (nb)
	{
		*(--nstr) = '0' + (nb % 10);
		nb /= 10;
	}
}

static char	*get_zero(void)
{
	char	*nstr;

	if (!malloc_free_p(sizeof(char) * 2, (void **)&nstr))
		return (NULL);
	nstr[0] = '0';
	nstr[1] = '\0';
	return (nstr);
}

char	*ft_itoa(int n)
{
	int				size;
	long long int	nb;
	char			*nstr;
	int				is_neg;

	if (n == 0)
		return (get_zero());
	nb = n;
	is_neg = (n < 0);
	size = ft_log10(n) + is_neg;
	if (!malloc_free_p(sizeof(char) * (size + 1), (void **)&nstr))
		return (NULL);
	if (is_neg)
	{
		*nstr = '-';
		nb *= -1;
	}
	ft_writenbr(nstr + size, nb);
	nstr[size] = '\0';
	return (nstr);
}
