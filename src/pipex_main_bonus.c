/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:58:08 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/21 22:15:46 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	clear_ppx(t_ppx *ppx, int is_parent, int exit_code)
{
	int		i;
	int		*pids;

	if (ppx->paths)
		strtab_clear(&ppx->paths);
	close_pipe(ppx->io, ppx->io + 1);
	if (ppx->argv)
		strtab_clear(&ppx->argv);
	if (is_parent)
	{
		pids = ppx->pids;
		i = CMD_MAX;
		while (--i)
			if (pids[i] && pids[i] > 0)
				waitpid(pids[i], NULL, 0);
	}
	return (exit_code);
}

static int	exec_single_cmd(t_ppx *ppx, int i, char *cmd, char **env)
{
	if (init_pipe(ppx, i) < 0)
		return (errno);
	ppx->pids[i] = fork();
	if (ppx->pids[i] < 0)
		return (close_pipe(ppx->pp, ppx->pp + 1)
			& repport_error("fork failed"));
	else if (ppx->pids[i] == 0)
	{
		close_pipe(ppx->pp, NULL);
		if (parse_validate_cmd(ppx->paths, cmd, &ppx->argv) == 0)
		{
			strtab_clear(&ppx->paths);
			dup2(*ppx->in, 0);
			dup2(*ppx->out, 1);
			if (execve(ppx->argv[0], ppx->argv, env) < 0)
				return (repport_execve_failed(ppx->argv[0]));
		}
		exit(clear_ppx(ppx, 0, errno));
	}
	close_pipe(ppx->in, ppx->out);
	ppx->rd_pipe = ppx->pp[0];
	return (EXIT_SUCCESS);
}

static void	waitpid_wrapper(int *pid, int *status, int flags)
{
	int	s;

	waitpid(*pid, &s, flags);
	if (s)
		*status = s >> 8;
	*pid = -1;
}

int	main(int argc, char **argv, char **env)
{
	t_ppx	ppx;
	int		here_doc;
	int		i;
	int		status;
	int		status2;

	ft_memclear(&ppx, sizeof(t_ppx));
	if (validate_pipex_input_args(argc, argv, &here_doc) != 0
		|| validate_io_files(ppx.io, argc, argv, here_doc) != 0)
		return (clear_ppx(&ppx, 1, errno));
	ppx.nb_cmds = argc - 3 - here_doc;
	argv += 2 + here_doc;
	ppx.paths = get_env_paths(env);
	i = -1;
	while (++i < ppx.nb_cmds)
		if (exec_single_cmd(&ppx, i, argv[i], env) != EXIT_SUCCESS)
			return (clear_ppx(&ppx, 1, errno));
	close_pipe(ppx.in, &ppx.rd_pipe);
	status = EXIT_SUCCESS;
	waitpid_wrapper(&ppx.pids[--i], &status, 0);
	while (--i >= 0)
		waitpid_wrapper(&ppx.pids[i], &status2, 0);
	return (clear_ppx(&ppx, 1, status));
}
