/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:25:05 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/02 17:44:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	size_t	nb;
	double	dec;
	int		sign;
	char	*dot;

	nb = 0.0f;
	dec = 0.0f;
	dot = ft_strchr(str, '.');
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
	while (*str && ft_isdigit(*str) || (*str == '.' && str++))
		nb = (nb * 10) + (*(str++) - '0');
	dec = (double)nb;
	if (!dot || (dot > str))
		return (sign * dec);
	return (sign * (dec / ft_pow(10, str - dot - 1)));
}
/*
int	main(int argc, char **argv)
{
	float	result;

	if (argc > 1)
	{
		result = ft_atof(argv[1]);
		printf("result : %.10f\n", result);
	}
	return (0);
}
*/
