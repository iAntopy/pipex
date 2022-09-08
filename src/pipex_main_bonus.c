/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 08:22:51 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clear_ppx(t_ppx *ppx, int exit_code)
{
	char	***cmds;
	int		*io;

	io = ppx->io_fds;
	if (*ppx->cmd_args)
	{
		cmds = ppx->cmd_args - 1;
		while (*(++cmds))
			strtab_clear(cmds);
	}
	if (ppx->paths)
		strtab_clear(&ppx->paths);
	if (io[0] && io[0] > 0)
		close(io[0]);
	if (io[1] && io[1] > 0)
		close(io[1]);
	return (exit_code);
}

void	close_pipe(int *pp, int close_mask)
{
	if ((close_mask & PIPE_RD) && pp[0] >= 3)
	{
		close(pp[0]);
		pp[0] = -1;
	}
	if ((close_mask & PIPE_WR) && pp[1] >= 3)
	{
		close(pp[1]);
		pp[1] = -1;
	}
}

static int	exec_single_cmd(int *infile, char **argv, char **env, int outfile)
{
	int	pid;
	int	status;
	int	pp[2];

	ft_memclear(pp, sizeof(pp));
	if (outfile)
		pp[1] = outfile;
	else if (pipe(pp) < 0)
		return (repport_error("pipe call failed"));
	pid = fork();
	if (pid < 0)
		return (check_cmd_exec_err(argv[0], -1, pp, pid));
	else if (pid == 0)
	{
		close_pipe(pp, PIPE_RD);
		dup2(*infile, 0);
		dup2(pp[1], 1);
		execve(argv[0], argv, env);
	}
	close_pipe(pp, PIPE_WR);
	close_pipe(infile, PIPE_RD);
	waitpid(pid, &status, 0);
	*infile = pp[0] + (status != EXIT_SUCCESS) * (status - pp[0]);
	return (check_cmd_exec_err(argv[0], status, pp, pid));
}

int	main(int argc, char **argv, char **env)
{
	t_ppx	ppx;
	int		here_doc;
	char	***cmds;
	int		*io;

	ft_memclear(&ppx, sizeof(t_ppx));
	if (validate_pipex_input_args(argc, argv, &here_doc) < 0
		|| validate_io_files(&ppx, &argc, &argv, here_doc) < 0
		|| parse_validate_cmds(&ppx, argc, argv, env) < 0)
		return (clear_ppx(&ppx, errno));
	cmds = ppx.cmd_args - 1;
	io = ppx.io_fds;
	while (*(++cmds))
		if (exec_single_cmd(io, *cmds, env, !*(cmds + 1) * io[1]) != 0)
			return (clear_ppx(&ppx, io[0]));
	return (clear_ppx(&ppx, EXIT_SUCCESS));
}
