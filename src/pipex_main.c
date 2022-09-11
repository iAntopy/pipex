/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/11 03:35:49 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	close_pipe(int *rd, int *wr)
{
//	printf("pid %d close_pipe 1 : errno : %d\n", getpid(), errno);
	if (rd && *rd >= 3)
	{
//		printf("pid %d close_pipe rd : closing : %d\n", getpid(), *rd);
		close(*rd);
		*rd = -1;
	}
//	printf("pid %d close_pipe 2 : errno : %d\n", getpid(), errno);
	if (wr && *wr >= 3)
	{
//		printf("pid %d close_pipe wr : closing : %d\n", getpid(), *wr);
		close(*wr);
		*wr = -1;
	}
//	printf("pid %d close_pipe 3 : errno : %d\n", getpid(), errno);
	return (0);
}

int	clear_ppx(t_ppx *ppx, int exit_code)
{
	int		*io;
	int		i;
	int		*pids;

	io = ppx->io;
	pids = ppx->pids;
	if (ppx->paths)
		strtab_clear(&ppx->paths);
//	printf("PARENT %d : infile and outfile before clear : %d, %d\n", getpid(), ppx->io[0], ppx->io[1]);
	close_pipe(io, io + 1);
//	printf("PARENT %d : infile and outfile after clear : %d, %d\n", getpid(), ppx->io[0], ppx->io[1]);
//	if (io[0] && io[0] > 0)
//		close(io[0]);
//	if (io[1] && io[1] > 0)
//		close(io[1]);
	i = CMD_MAX;
	while (--i)
		if (pids[i] && pids[i] > 0)
			waitpid(pids[i], NULL, 0);
//	printf("CLEAR_PPX : exit_code vs errno : %d vs %d\n", exit_code, errno);
	return (exit_code);
}

int	clear_ppx_child(t_ppx *ppx, char ***argv, int exit_code)
{
//	printf("CHILD clear_ppx_child 1 : errno : %d\n", errno);
	strtab_clear(&ppx->paths);
//	printf("CHILD clear_ppx_child 2 : errno : %d\n", errno);
	strtab_clear(argv);
//	printf("CHILD clear_ppx_child 3 : errno : %d\n", errno);
	close_pipe(ppx->in, ppx->out);
//	printf("CHILD clear_ppx_child 4 : errno : %d\n", errno);
	return (exit_code);
}
/*
	int		*io;

	printf("CHILD CLEAR_PPX at start exit_code vs errno : %d vs %d\n", exit_code, errno);
	io = ppx->io;
	printf("CHILD : ppx->paths ptr : %p\n", ppx->paths);
	if (ppx->paths)
		strtab_clear(&ppx->paths);
	printf("CHILD : io fds : %d, %d\n", io[0], io[1]);
	printf("CHILD CLEAR_PPX before close io[0] exit_code vs errno : %d vs %d\n", exit_code, errno);
//	if (io[0] && io[0] > 0)
//		close(io[0]);
	printf("CHILD CLEAR_PPX before close io[1] exit_code vs errno : %d vs %d\n", exit_code, errno);
	close_pipe(NULL, io + 1);
	if (io[1] && io[1] > 0)
		close(io[1]);
	printf("CHILD CLEAR_PPX at end exit_code vs errno : %d vs %d\n", exit_code, errno);
	return (exit_code);
}
*/

static int	init_pipe(t_ppx *ppx, int i)
{
	int	is_first;
	int	is_last;

	is_first = (i == 0);
	is_last = (i == (ppx->nb_cmds - 1));
	ppx->in = &ppx->rd_pipe;
	ppx->out = ppx->pp + 1;
	if (!is_last)
	{
//		printf("OPENING PIPE !!\n");
		if (pipe(ppx->pp) < 0)
			return (repport_error("pipe call failed"));
	}
	if (is_first)
		ppx->in = ppx->io;
	else if (is_last)
		ppx->out = ppx->io + 1;
	return (0);
}

static int	exec_single_cmd(t_ppx *ppx, int i, char *cmd, char **env)
{
	char	**argv;

//	printf("PARENT %d : start : i -> %d : in %d, rd %d, out %d\n", getpid(), i, (!!ppx->in) ? (*ppx->in):(-1), ppx->rd_pipe, (!!ppx->out) ? (*ppx->out): (-1));
	if (init_pipe(ppx, i) < 0)
		return (errno);
//	printf("PARENT %d : post init pipe : i -> %d : in %d, rd %d, out %d\n", getpid(), i, *ppx->in, ppx->rd_pipe, *ppx->out);
	ppx->pids[i] = fork();
	if (ppx->pids[i] < 0)
		return (close_pipe(ppx->pp, ppx->pp + 1) & repport_error("fork failed"));
	else if (ppx->pids[i] == 0)
	{
//		printf("CHILD %d : starts\n", getpid());
		if (parse_validate_cmd(ppx->paths, cmd, &argv) == 0)
		{
			strtab_clear(&ppx->paths);
			dup2(*ppx->in, 0);
			dup2(*ppx->out, 1);
			execve(argv[0], argv, env);
		}
		exit(clear_ppx_child(ppx, &argv, errno));
	}
//	printf("PARENT %d : post fork : i -> %d : in %d, rd %d, out %d\n", getpid(), i, *ppx->in, ppx->rd_pipe, *ppx->out);
	close_pipe(ppx->in, ppx->out);
	ppx->rd_pipe = ppx->pp[0];
//	printf("PARENT %d : at exit : i -> %d : in %d, rd %d, out %d\n", getpid(), i, *ppx->in, ppx->rd_pipe, *ppx->out);
	return (EXIT_SUCCESS);
}
/*
static int	exec_single_cmd(t_ppx *ppx, int i, char *cmd, char **env)
{
	int		pp[2];
	char	**argv;

	ft_memclear(pp, sizeof(pp));
	printf("PARENT %d : i (%d) == (nb_cmds - 1) (%d) ? %d\n", getpid(), i, ppx->nb_cmds - 1, (i == (ppx->nb_cmds - 1)));
	if (i == (ppx->nb_cmds - 1))
	{
		printf("PARENT %d : Not opening pipe. Just take io[1] aka outfile.\n", getpid());
		pp[1] = ppx->io[1];
	}
	else if (pipe(pp) < 0)
		return (repport_error("pipe call failed"));
	else
		printf("PARENT %d: Opened pipe. infile : %d, rd : %d, wr : %d\n", getpid(), ppx->io[0], pp[0], pp[1]);
	ppx->pids[i] = fork();
	if (ppx->pids[i] < 0)
		return (close_pipe(pp, pp + 1) & repport_error("fork failed"));
	else if (ppx->pids[i] == 0)
	{
		printf("CHILD : trying to parse_validate_cmd()\n");
		if (parse_validate_cmd(ppx->paths, cmd, &argv) == 0)
		{
			strtab_clear(&ppx->paths);
			dup2(ppx->io[0], 0);
			dup2(pp[1], 1);
			execve(argv[0], argv, env);
		}
		strtab_clear(&ppx->paths);
		if (i == (ppx->nb_cmds - 1))
		{
			ppx->io[1] = -1;
			exit(clear_ppx_child(ppx, &argv, NULL, errno));
		}
		else
			exit(clear_ppx_child(ppx, &argv, pp + 1, errno));
	}
	printf("PARENT %d : infile and pipe wr before closing : %d, %d\n", getpid(), ppx->io[0], pp[1]);
	close_pipe(&ppx->io[0], pp + 1);
	printf("PARENT %d : infile and pipe wr after closing : %d, %d\n", getpid(), ppx->io[0], pp[1]);
	ppx->io[0] = pp[0];
	return (0);
}
*/
	/*	
		if (parse_validate_cmd(ppx->paths, cmd, &argv) != 0)
		{
			printf("CHILD argv ptr : %p\n", argv);
			printf("CHILD errno after parse_validate : %d\n", errno);
//			strtab_clear(&argv);
			exit(clear_ppx_child(ppx, &argv, pp + 1, errno));
//			exit(close_pipe(NULL, pp + 1) & errno);
			//printf("CHILD errno after close_pipe : %d\n", errno);
			//exit(clear_ppx_child(ppx, errno));
//			exit(errno);
		}
//		close_pipe(pp, NULL);
		dup2(ppx->io[0], 0);
		dup2(pp[1], 1);
		strtab_clear(&ppx->paths);
		if (execve(argv[0], argv, env) < -1)
		{
			printf("WoW  CHILD : execve failed !\n");
//			strtab_clear(&argv);
//			exit(close_pipe(NULL, pp + 1) & repport_error("execve failed"));
			exit(clear_ppx_child(ppx, &argv, pp + 1, errno));
		}
	}
	close_pipe(&ppx->io[0], pp + 1);
	ppx->io[0] = pp[0];
	return (0);
}
*/

static void	waitpid_wrapper(int *pid, int *status, int flags)
{
	int	s;

	waitpid(*pid, &s, flags);
//	printf("pid %d exited with status %d\n", *pid, s);
	if (status)
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
//	printf("status returned from pid %d : %d\n", ppx.pids[i], status);
	while (--i >= 0)
	{
		waitpid_wrapper(&ppx.pids[i], &status2, 0);
		if (status2 != EXIT_SUCCESS)
			printf("WoW ! pid %d returned with status : %d\n", ppx.pids[i], status2);
	}
	return (clear_ppx(&ppx, status));
}
