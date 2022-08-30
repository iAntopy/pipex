/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:51:29 by iamongeo          #+#    #+#             */
/*   Updated: 2022/03/28 15:51:31 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec_putnbr(long long int n)
{
	if (n > 9)
		rec_putnbr(n / 10);
	ft_putchar('0' + (n % 10));
}

void	ft_putnbr(int nbr)
{
	long long int	n;

	n = (long long int)nbr;
	write(1, "-", (n < 0));
	n *= 1 - (2 * (n < 0));
	rec_putnbr(n);
}
/*
int	main(int argc, char *argv[])
{
	int	nbr;

	if (argc > 1)
	{
		nbr = atoi(argv[1]);
		ft_putnbr(nbr);
	}
	return (0);
}
*/
