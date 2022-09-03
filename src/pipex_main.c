/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/03 00:23:41 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clear_ppx(t_ppx *ppx, char **fn, int exit_code)
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
	if (fn && *fn)
		malloc_free_p(0, (void **)fn);
	if (exit_code == EXIT_OUTPUT_FILE_ERR)
		return (report_error("Output file permission denied."));
	else if (exit_code == EXIT_OUTPUT_OPEN_ERR)
		return (report_error("Output file open call failed."));
	else if (exit_code == EXIT_INVALID_CMD)
		return (-1);
	return (EXIT_SUCCESS);
}

static int	validate_input_file(int io[2], char **argv, int here_doc)
{
	char	*fn;

	if (here_doc)
		io[0] = get_here_doc_input(argv[2]);
	else if (find_file_in_env(argv[1], NULL, &fn, R_OK))
		io[0] = open(fn, O_RDONLY);
	else
		return (report_error("Input file not found or permission denied.",
				EXIT_INPUT_FILE_ERR));
	malloc_free_p(0, (void **)&fn);
	if (io[0] < 0)
		return (report_error("Input file open failed.", EXIT_INPUT_OPEN_ERR));
	return (0);
}

static int	validate_output_file(int io[2], int argc, char **argv, int here_doc)
{
	if (find_file_in_env(argv[*argc - 1], NULL, &fn, 0) && access(fn, W_OK) < 0)
		return (clear_ppx(ppx, &fn, EXIT_OUTPUT_FILE_ERR));
	if (here_doc)
		io[1] = open(argv[*argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		io[1] = open(argv[*argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	malloc_free_p(0, (void **)&fn);
	if (io[1] < 0)
		return (clear_ppx(ppx, &fn, EXIT_OUTPUT_OPEN_ERR));
	return (0);
}

int	validate_io_files(t_ppx *ppx, int *argc, char ***argv_p)
{
	char	**argv;
	char	*fn;
	int		*io;
	int		here_doc;

	io = ppx->io_fds;
	here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	if (validate_input_file(io, *argv_p, here_doc) < 0)
		return (-1);
	if (validate_output_file(io, argc, *argv_p, here_doc) < 0)
		return (-1);

/*
	if (here_doc)
		io[0] = get_here_doc_input(argv[2]);
	else if (find_file_in_env(argv[1], NULL, &fn, R_OK))
		io[0] = open(fn, O_RDONLY);
	else
		return (report_error("Input file not found or permission denied.",
				EXIT_INPUT_FILE_ERR));
	malloc_free_p(0, (void **)&fn);
	if (io[0] < 0)
		return (report_error("Input file open failed.", EXIT_INPUT_OPEN_ERR));
	if (find_file_in_env(argv[*argc - 1], NULL, &fn, 0) && access(fn, W_OK) < 0)
		return (clear_ppx(ppx, &fn, EXIT_OUTPUT_FILE_ERR));
	if (here_doc)
		io[1] = open(argv[*argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		io[1] = open(argv[*argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	malloc_free_p(0, (void **)&fn);
	if (io[1] < 0)
		return (clear_ppx(ppx, &fn, EXIT_OUTPUT_OPEN_ERR));
*/
	*argv_p += 2 + here_doc;
	*argc -= (3 + here_doc);
	return (0);
}

int	parse_validate_cmds(t_ppx *ppx, int argc, char **argv, char **env)
{
	int		i;
	char	***cmds;
	char	*filename;

	printf("Enter validate cmds : argc %d, argv[0] %s\n", argc, argv[0]);
	cmds = ppx->cmd_args;
	ppx->paths = get_env_paths(env);
	i = -1;
	printf("Entering while loop");
	while (++i < argc)
	{
		ppx->sc = substitute_spaces_in_substr(argv[i]);
		cmds[i] = ft_split_space(argv[i]);
		restore_spaces_in_substr(cmds[i], ppx->sc);
		if (!find_file_in_paths(cmds[i][0], ppx->paths, &filename, X_OK))
		{
			fperror(RED_BC"<[ Pipex ERROR : %s : No command named %s ]>"WHITE_C,
				__FUNCTION__, cmds[i][0]);
			return (clear_ppx(ppx, &filename, EXIT_INVALID_CMD));
		}
		malloc_free_p(0, (void **)&cmds[i][0]);
		cmds[i][0] = filename;
	}
	ppx->nb_cmds = i;
	return (0);
}

void	print_cmds(t_ppx *ppx)
{
	char	***cmds;

	cmds = ppx->cmd_args;
	while (*cmds)
		strtab_print(*(cmds++));
}

int	main(int argc, char **argv, char **env)
{
	t_ppx	ppx;

	if (argc < 5 || argc > CMD_MAX)
		return (report_error("Pipex takes from 4-64 arguments.",
				EXIT_WRONG_NB_INPUTS));
	printf("PIPE_RD, PIPE_WR : %d, %d\n", PIPE_RD, PIPE_WR);
	ft_memclear(&ppx, sizeof(t_ppx));
	printf("validate io\n");
	if (validate_io_files(&ppx, &argc, &argv) < 0)
		return (errno);
	printf("validate cmds\n");
	if (parse_validate_cmds(&ppx, argc, argv, env) < 0)
		return (errno);
	print_cmds(&ppx);
	printf("exec cmds\n");
	if (exec_cmd_chain(&ppx, env) < 0)
		return (errno);
	printf("EXIT_SUCCESS\n");
	return (clear_ppx(&ppx, NULL, EXIT_SUCCESS));
}
