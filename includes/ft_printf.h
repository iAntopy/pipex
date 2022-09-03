/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:16:50 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/07 15:48:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

# define X_BASE "0123456789abcdef"
# define XX_BASE "0123456789ABCDEF"
# define DEC_BASE "0123456789"

int	ft_printf(const char *fmt, ...);
int	ft_vprintf(const char *fmt, va_list *ap);

#endif
