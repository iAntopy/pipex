/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:18:30 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/03 00:18:03 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "pipex.h"

int	report_error(char *err)
{
	fperror(RED_BC"<[ PIPEX ERROR :: %s :: %s ]>", err);
	ft_printf(WHITE_C);
	return (-1);
}

int	report_child_exec_err(char *cmd, int status)
{
	fperror(RED_BC"<[ PIPEX ERROR :: child command %s failed :: (%d): %s ]>",
		cmd, status, strerror(errno));
	ft_printf(WHITE_C);
	return (status);
}
