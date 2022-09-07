/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:24:41 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/11 20:35:11 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int nb, int exp)
{
	int	res;

	if (!exp)
		return (1);
	if (!nb || (exp < 0))
		return (0);
	res = nb;
	while (--exp)
		res *= nb;
	return (res);
}
