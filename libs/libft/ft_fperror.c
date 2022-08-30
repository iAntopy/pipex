/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fperror.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:30:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/12 23:08:42 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include "ft_printf.h"

void	*fperror(char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	ft_vprintf(fmt, &ap);
	perror(" ");
	va_end(ap);
	return (NULL);
}
