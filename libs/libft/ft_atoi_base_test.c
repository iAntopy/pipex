/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 22:40:05 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/03 23:07:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main()
{
	int	result;

	result = ft_atoi_base("              -000000000123+++_+_+", 10, "0123456789");
	ft_printf("result : %d\n", result);
	return (0);
}