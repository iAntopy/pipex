/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:23:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/10 23:30:02 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec_putnbr_base(size_t n, char *base, size_t radix, size_t *count)
{
	if (n >= radix)
		rec_putnbr_base(n / radix, base, radix, count);
	*count += write(1, base + (n % radix), 1);
}

static void	ft_putnbr_base(ssize_t n, char *base, size_t radix, size_t *count)
{
	*count += write(1, "-", n < 0);
	rec_putnbr_base((size_t)(n * (1 - (2 * (n < 0)))), base, radix, count);
}

static void	ft_printstr(const char *str, size_t *count)
{
	if (!str)
		*count += write(1, "(null)", 6);
	else
		while (*str)
			*count += write(1, str++, 1);
}

static void	print_flag(char flag, va_list *ap, size_t *count)
{
	if (flag == 'c')
	{
		flag = (char)va_arg(*ap, int);
		*count += write(1, &flag, 1);
	}
	else if (flag == 's')
		ft_printstr((char *)va_arg(*ap, char *), count);
	else if (flag == 'p')
	{
		*count += write(1, "0x", 2);
		rec_putnbr_base((size_t)va_arg(*ap, size_t), X_BASE, 16, count);
	}
	else if (flag == 'd' || flag == 'i')
		ft_putnbr_base((ssize_t)va_arg(*ap, int), DEC_BASE, 10, count);
	else if (flag == 'u')
		rec_putnbr_base((size_t)va_arg(*ap, unsigned int), DEC_BASE, 10, count);
	else if (flag == 'x')
		rec_putnbr_base((size_t)va_arg(*ap, unsigned int), X_BASE, 16, count);
	else if (flag == 'X')
		rec_putnbr_base((size_t)va_arg(*ap, unsigned int), XX_BASE, 16, count);
	else if (flag == '%')
		*count += write(1, &flag, 1);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	size_t	count;

	count = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
			print_flag(*(++fmt), &ap, &count);
		else
			count += write(1, fmt, 1);
		fmt++;
	}
	va_end(ap);
	return (count);
}
