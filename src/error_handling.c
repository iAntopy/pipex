/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_man.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:18:30 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 08:21:48 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	repport_bad_inputs(int argc)
{
	errno = EINVAL;
	ft_printf(RED_BC"<[ PIPEX ERROR :: wrong nb of args received (%d) ]>",
		argc - 1);
	ft_printf(WHITE_C"\n\n pipex arguments format : \n");
	ft_printf("\teither\t{infile} {cmd1} {cmd2} {outfile}\n");
	ft_printf("\tor\there_doc {LIMITER} {cmd1} {cmd2} {outfile}\n");
	return (-1);
}

int	repport_error(char *err)
{
	fperror(RED_BC"<[ PIPEX ERROR :: %s ]>", err);
	ft_printf(WHITE_C);
	return (-1);
}

int	repport_bad_cmd(char *cmd, int status)
{
	if (status == EXIT_CMD_NOT_FOUND)
		fperror(RED_BC"<[ PIPEX ERROR :: Could not locate %s command. ]>", cmd);
	else if (status == EXIT_CMD_NOT_EXE)
		fperror(RED_BC"<[ PIPEX ERROR :: Command %s not executable. ]>", cmd);
	ft_printf(WHITE_C);
	return (-1);
}

int	check_cmd_exec_err(char *cmd, int status, int *pp, int pid)
{
	if (pid < 0)
	{
		close_pipe(pp, PIPE_RD | PIPE_WR);
		fperror(RED_BC"<[ PIPEX ERROR :: fork call failed ]>"WHITE_C);
	}
	else if (status != EXIT_SUCCESS)
	{
		close_pipe(pp, PIPE_RD | PIPE_WR);
		fperror(RED_BC"<[ PIPEX ERROR :: child cmd %s failed ]>"WHITE_C, cmd);
	}
	return (status);
}

int	validate_pipex_input_args(int argc, char **argv, int *here_doc)
{
	if (argc < 2)
		return (repport_bad_inputs(argc));
	*here_doc = (ft_strcmp("here_doc", argv[1]) == 0);
	argc -= *here_doc;
	if ((argc < 5) || ((argc - 3) > CMD_MAX))
		return (repport_bad_inputs(argc + *here_doc));
	return (0);
}
