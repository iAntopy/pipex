/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:49:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/04 03:31:00 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pipe(int pp[2], int close_mask)
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

static void	child_proc_execve(int in_file, int pp[2], char **argv, char **env)
{
	close_pipe(pp, PIPE_RD);
	dup2(in_file, 0);
	dup2(pp[1], 1);
	if (execve(argv[0], argv, env) < 0)
		fperror("Child process failed to execve cmd : %s\n", argv[0]);
}

static int	exec_single_cmd(int in_file, char **argv, char **env)
{
	int	pid;
	int	status;
	int	pp[2];

	ft_memclear(pp, sizeof(pp));
	if (pipe(pp) < 0)
		return (repport_error("pipe call failed"));
	pid = fork();
	if (pid < 0)
	{
		close_pipe(pp, PIPE_RD | PIPE_WR);
		return (repport_error("fork call failed"));
	}
	else if (pid == 0)
		child_proc_execve(in_file, pp, argv, env);
	close_pipe(pp, PIPE_WR);
	close(in_file);
	waitpid(pid, &status, 0);
	if (status != EXIT_SUCCESS)
	{
		close_pipe(pp, PIPE_RD | PIPE_WR);
		return (repport_child_exec_err(argv[0], status));
	}
	return (pp[0]);
}

static int	exec_last_cmd(int in_file, char **argv, char **env, int out_file)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (repport_error("fork call failed"));
	else if (pid == 0)
	{
		dup2(in_file, 0);
		dup2(out_file, 1);
		execve(argv[0], argv, env);
	}
	close(in_file);
	close(out_file);
	waitpid(pid, &status, 0);
	if (status != 0)
		return (repport_child_exec_err(argv[0], status));
	return (out_file);
}

int	exec_cmd_chain(t_ppx *ppx, char **env)
{
	char	***cmds;
	int		*io;
	int		in_file;

	io = ppx->io_fds;
	in_file = io[0];
	cmds = ppx->cmd_args;
	while (*(cmds + 1) && (in_file >= 0))
		in_file = exec_single_cmd(in_file, *(cmds++), env);
	if (in_file < 0)
		return (-1);
	return (exec_last_cmd(in_file, *cmds, env, io[1]));
}
