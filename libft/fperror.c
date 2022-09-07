/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fperror.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:30:32 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/10 23:30:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <errno.h>

void	fperror(char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	ft_vprintf(fmt, &ap);
	perror(" ");
	va_end(ap);
}
