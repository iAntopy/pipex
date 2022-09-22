/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_errno.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 21:17:20 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/19 21:18:26 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

int	set_errno(int n)
{
	errno = n;
	return (1);
}
