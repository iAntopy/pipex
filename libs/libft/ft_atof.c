/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:25:05 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/11 20:44:27 by iamongeo         ###   ########.fr       */
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
	printf("nb : %zu\n", nb);
	dec = (double)nb;
	if (!dot || (dot > str))
		return (sign * dec);
	printf("dot, str, str - dot - 1 : %p,  %p, %zu\n", dot, str, str - dot - 1);
	printf("double nb : %.10f\n", dec);
	return (sign * (dec / ft_pow(10, str - dot - 1)));
	/*
	if (*(str++) == '.' && ft_isdigit(*str))
	{
		while (*str && ft_isdigit(*str))
			str++;
			//dec_place++;
		printf("checking decimal and str is at '\\0' : %d\n", (*str == '\0'));
		printf("char at str ptr : %c\n", *str);
		while (*(--str) != '.')
		{
//			nb = (nb * 10) + (*(str++) - '0');
			dec = (dec / 10) + (*str - '0');
			printf("decimal digit : %d\n", *str - '0');
			printf("current dec : %.10f\n", dec);
		}
	}
	return (sign * (nb + dec / 10));
	*/
}

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
