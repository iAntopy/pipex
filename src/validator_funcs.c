/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 21:50:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/08 08:40:12 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	validate_input_file(int io[2], int argc, char **argv, int here_doc)
{
	char	*fn;

	fn = NULL;
	if (here_doc)
		io[0] = get_here_doc_input(argv[2], argc - 5);
	else if (find_file_in_env(argv[1], NULL, &fn, R_OK))
		io[0] = open(fn, O_RDONLY);
	else
		return (repport_error("Input file not found or permission denied."));
	malloc_free_p(0, (void **)&fn);
	if (io[0] < 0)
		return (repport_error("Input file open failed."));
	else if (io[0] == 0)
		return (-1);
	return (0);
}

static int	validate_output_file(int io[2], int argc, char **argv, int here_doc)
{
	char	*fn;

	if (find_file_in_env(argv[argc - 1], NULL, &fn, 0) && access(fn, W_OK) < 0)
	{
		malloc_free_p(0, (void **)&fn);
		return (repport_error("Output file permission denied."));
	}
	if (here_doc)
		io[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		io[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	malloc_free_p(0, (void **)&fn);
	if (io[1] < 0)
		return (repport_error("Output file open failed."));
	return (0);
}

int	validate_io_files(t_ppx *ppx, int *argc, char ***argv_p, int here_doc)
{
	int		*io;

	io = ppx->io_fds;
	if (validate_input_file(io, *argc, *argv_p, here_doc) < 0)
		return (-1);
	if (validate_output_file(io, *argc, *argv_p, here_doc) < 0)
		return (-1);
	*argv_p += 2 + here_doc;
	*argc -= (3 + here_doc);
	return (0);
}

int	parse_validate_cmds(t_ppx *ppx, int argc, char **argv, char **env)
{
	int		i;
	char	***cmds;
	char	*filename;
	int		status;

	cmds = ppx->cmd_args;
	ppx->paths = get_env_paths(env);
	status = 0;
	i = -1;
	while (++i < argc)
	{
		ppx->sc = substitute_spaces_in_substr(argv[i]);
		cmds[i] = ft_split_space(argv[i]);
		restore_spaces_in_substr(cmds[i], ppx->sc);
		if (!find_file_in_paths(cmds[i][0], ppx->paths, &filename, F_OK))
			status = repport_bad_cmd(cmds[i][0], EXIT_CMD_NOT_FOUND);
		else if (access(filename, X_OK) < 0)
			status = repport_bad_cmd(cmds[i][0], EXIT_CMD_NOT_EXE);
		if (status)
			return (-1);
		malloc_free_p(0, (void **)&cmds[i][0]);
		cmds[i][0] = filename;
	}
	ppx->nb_cmds = i;
	return (0);
}
