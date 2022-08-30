/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:49:49 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/29 06:36:02 by iamongeo         ###   ########.fr       */
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
	printf("child proc : in_file, pp[0], pp[1] : %d, %d, %d \n", in_file, pp[0], pp[1]);
	printf("CHILD closing read side of pipe : %d\n", pp[0]);
	close_pipe(pp, PIPE_RD);
	dup2(in_file, 0);
	dup2(pp[1], 1);
	execve(argv[0], argv, env);
}

static int	exec_single_cmd(int in_file, char **argv, char **env)
{
	int	pid;
	int	status;
	int	pp[2];

	ft_memclear(pp, sizeof(pp));
	if (pipe(pp) < 0)
		return (PPX_ERROR("pipe call failed", EXIT_PIPE_ERR));
	printf("\nStart exec single cmd : in_file, pp[0], pp[1] : %d, %d, %d\n", in_file, pp[0], pp[1]);
	pid = fork();
	if (pid < 0)
	{
		printf("PARENT closing read/write sides of pipe : %d, %d\n", pp[0], pp[1]);
		close_pipe(pp, PIPE_RD | PIPE_WR);
		return (PPX_ERROR("fork call failed", EXIT_FORK_ERR));
	}
	else if (pid == 0)
		child_proc_execve(in_file, pp, argv, env);
	printf("PARENT closing write side of pipe : %d\n", pp[1]);
	close_pipe(pp, PIPE_WR);
	printf("PARENT closing in_file : %d\n", in_file);
	close(in_file);
	waitpid(pid, &status, 0);
	if (status != EXIT_SUCCESS)
	{
		close_pipe(pp, PIPE_RD | PIPE_WR);
		return (report_child_exec_err(argv[0], status));
	}
	return (pp[0]);
}

static int	exec_last_cmd(int in_file, char **argv, char **env, int out_file)
{
	int	pid;
	int	status;

	printf("\nStart exec last cmd : in_file, out_file : %d, %d\n", in_file, out_file);
	pid = fork();
	if (pid < 0)
		return (PPX_ERROR("fork call failed", EXIT_FORK_ERR));
	else if (pid == 0)
	{
		dup2(in_file, 0);
		dup2(out_file, 1);
		execve(argv[0], argv, env);
	}
	printf("PARENT closing in_file : %d\n", in_file);
	close(in_file);
	printf("PARENT closing out_file : %d\n", out_file);
	close(out_file);
	waitpid(pid, &status, 0);
	if (status != 0)
		return (report_child_exec_err(argv[0], status));
	return (out_file);
}

int	exec_cmd_chain(t_ppx *ppx, char **env)
{
	char	***cmds;
	int	*io;
	int	in_file;
	
	io = ppx->io_fds;
	in_file = io[0];
	cmds = ppx->cmd_args;
	while (*(cmds + 1) && (in_file >= 0))
		in_file = exec_single_cmd(in_file, *(cmds++), env);
	if (in_file < 0)
		return (in_file);
	in_file = exec_last_cmd(in_file, *cmds, env, io[1]);
	return (in_file);
}
