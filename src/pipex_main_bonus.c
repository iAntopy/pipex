/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/10 06:44:39 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

int	clear_ppx(t_ppx *ppx, int exit_code)
{
	int		*io;
	int		i;
	int		*pids;

	io = ppx->io;
	pids = ppx->pids;
	if (ppx->paths)
		strtab_clear(&ppx->paths);
	if (io[0] && io[0] > 0)
		close(io[0]);
	if (io[1] && io[1] > 0)
		close(io[1]);
	i = CMD_MAX;
	while (--i)
		if (pids[i] && pids[i] > 0)
			waitpid(pids[i], NULL, 0);
	return (exit_code);
}

int	close_pipe(int *rd, int *wr)
{
	if (rd && *rd >= 3)
	{
		close(*rd);
		*rd = -1;
	}
	if (wr && *wr >= 3)
	{
		close(*wr);
		*wr = -1;
	}
	return (0);
}

static int	exec_single_cmd(t_ppx *ppx, int i, char *cmd, char **env)
{
	int		pp[2];
	char	**argv;

	ft_memclear(pp, sizeof(pp));
	if (i == (ppx->nb_cmds - 1))
		pp[1] = ppx->io[1];
	else if (pipe(pp) < 0)
		return (repport_error("pipe call failed"));
	ppx->pids[i] = fork();
	if (ppx->pids[i] < 0)
		return (close_pipe(pp, pp + 1) & repport_error("fork failed"));
	else if (ppx->pids[i] == 0)
	{
		close_pipe(pp, NULL);
		if (parse_validate_cmd(ppx->paths, cmd, &argv) != 0)
			exit(close_pipe(pp, pp + 1) & clear_ppx(ppx, errno));
		dup2(ppx->io[0], 0);
		dup2(pp[1], 1);
		if (execve(argv[0], argv, env) < -1)
			exit(close_pipe(pp, pp + 1) & repport_error("execve failed"));
	}
	close_pipe(&ppx->io[0], pp + 1);
	ppx->io[0] = pp[0];
	return (0);
}

static void	waitpid_wrapper(int *pid, int *status, int flags)
{
	waitpid(*pid, status, flags);
	*pid = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_ppx	ppx;
	int		here_doc;
	int		i;
	int		status;

	ft_memclear(&ppx, sizeof(t_ppx));
	if (validate_pipex_input_args(argc, argv, &here_doc) != 0
		|| validate_io_files(ppx.io, argc, argv, here_doc) != 0)
		return (clear_ppx(&ppx, errno));
	ppx.nb_cmds = argc - 3 - here_doc;
	argv += 2 + here_doc;
	ppx.paths = get_env_paths(env);
	i = -1;
	while (++i < ppx.nb_cmds)
		if (exec_single_cmd(&ppx, i, argv[i], env) != EXIT_SUCCESS)
			return (clear_ppx(&ppx, errno));
	status = EXIT_SUCCESS;
	waitpid_wrapper(&ppx.pids[--i], &status, 0);
	while (--i >= 0)
		waitpid_wrapper(&ppx.pids[i], NULL, 0);
	return (clear_ppx(&ppx, status));
}
