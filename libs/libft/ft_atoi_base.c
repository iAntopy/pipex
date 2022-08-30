/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:39:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/04 01:40:06 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_base_index(const char digit, const char *base_str, int *idx)
{
	int			i;

	if (!base_str)
		return (-1);
	i = -1;
	while (base_str[++i])
	{
		if (base_str[i] == digit)
		{
			*idx = i;
			return (1);
		}
	}
	return (0);

}

// Assumes base is valid
int	ft_atoi_base(const char *str, int base, const char *base_str)
{
	ssize_t	nb;
	int		sign;
	int		digit;

	nb = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (0);
	if (*str && ft_issign(*str))
	{
		if (!find_base_index(*(str + 1), base_str, &digit))
			return (0);
		sign -= 2 * (*str == '-');
		str++;
	}
	while (*str && find_base_index(*(str++), base_str, &digit))
		nb = (nb * base) + digit;
	return (sign * nb);
}
