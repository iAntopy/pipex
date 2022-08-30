/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:18:30 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/29 05:46:53 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "pipex.h"

int	report_error(char *err, const char *func_name, int exit_code)
{
	fperror(RED_BC"<[ PIPEX ERROR : %s : %s ]>", func_name, err);
	ft_printf(WHITE_C);
	return (exit_code);
}

int	report_child_exec_err(char *cmd, int status)
{
	fperror(RED_BC"<[ PIPEX ERROR :: command %s failed :: (%d): %s ]>", cmd, status, strerror(errno));
	ft_printf(WHITE_C);
	return (EXIT_CMD_EXEC_ERR);
}
