/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:39:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 14:37:10 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_issign(int c)
{
	return (c == '+' || c == '-');
}

int	ft_isspace(int c)
{
	return (c == ' ' || (9 <= c && c <= 13));
}	

int	ft_atoi(const char *str)
{
	unsigned long long int	nb;
	int						sign;

	nb = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str && ft_issign(*str))
	{
		if (!ft_isdigit(*(str + 1)))
			return (0);
		sign -= 2 * (*str == '-');
		str++;
	}
	while (*str && ft_isdigit(*str) && (nb < LLONG_MAX))
		nb = (nb * 10) + (*(str++) - '0');
	if (nb > LLONG_MAX)
		return (-1 + (sign == -1));
	return (sign * nb);
}
