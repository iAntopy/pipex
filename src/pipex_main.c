/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/09 05:42:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clear_ppx(t_ppx *ppx, int exit_code)
{
	char	***cmds;
	int		*io;
	int		i;
	int		*pids;
	int		status;

	io = ppx->io;
	pids = ppx->pids;
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
	i = CMD_MAX;
	while (--i)
		if (pids[i] && pids[i] > 0)
			waitpid(ppx->pids[i], &status, 0);
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

static int	exec_single_cmd(t_ppx *ppx, int i, char **argv, char **env)
{
	int	pp[2];

	ft_memclear(pp, sizeof(pp));
	if (i == (ppx->nb_cmds - 1))
		pp[1] = ppx->io[1];
	else if (pipe(pp) < 0)
		return (repport_error("pipe call failed"));
	ppx->pids[i] = fork();
	if (ppx->pids[i] < 0)
	{
		close_pipe(pp, PIPE_RD | PIPE_WR);
		return (repport_error("fork() call failed"));
	}
	else if (ppx->pids[i] == 0)
	{
		close_pipe(pp, PIPE_RD);
		dup2(ppx->io[0], 0);
		dup2(pp[1], 1);
		if (execve(argv[0], argv, env) < -1)
			return (repport_error("execve() call failed"));
	}
	close_pipe(pp, PIPE_WR);
	close_pipe(ppx->io, PIPE_RD);
	ppx->io[0] = pp[0];
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_ppx	ppx;
	int		here_doc;
	char	***cmds;
	int		*io;
	int		i;

	ft_memclear(&ppx, sizeof(t_ppx));
	if (validate_pipex_input_args(argc, argv, &here_doc) < 0
		|| validate_io_files(&ppx, &argc, &argv, here_doc) < 0
		|| parse_validate_cmds(&ppx, argc, argv, env) < 0)
		return (clear_ppx(&ppx, errno));
	cmds = ppx.cmd_args - 1;
	io = ppx.io;
	i = -1;
	while (++i < ppx.nb_cmds)
		if (exec_single_cmd(&ppx, i, ppx.cmd_args[i], env) != EXIT_SUCCESS)
			return (clear_ppx(&ppx, errno));
	while (--i)
	{
		waitpid(ppx.pids[i], &here_doc, 0);
		if (here_doc != EXIT_SUCCESS)
			return (repport_cmd_exec_failure(ppx.cmd_args[i][0], here_doc));
		ppx.pids[i] = -1;
	}
	return (clear_ppx(&ppx, EXIT_SUCCESS));
}
