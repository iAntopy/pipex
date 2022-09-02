/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/02 16:40:56 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clear_ppx(t_ppx *ppx, char **fn, int exit_code)
{
	char	***cmds;
	int		*io;

	printf("CLEARING PPX !!\n");
	if (*ppx->cmd_args)
	{
		cmds = ppx->cmd_args - 1;
		io = ppx->io_fds;
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
		return (PPX_ERROR("Output file write permission denied.", exit_code));
	else if (exit_code == EXIT_OUTPUT_OPEN_ERR)
		return (PPX_ERROR("Output file open call failed.", exit_code));
	else if (exit_code == EXIT_INVALID_CMD)
		return (exit_code);
	return (EXIT_SUCCESS);
}

int	validate_io_files(t_ppx *ppx, int *argc, char ***argv_p)
{
	char	**argv;
	char	*fn;
	int		*io;
	int		here_doc;

	io = ppx->io_fds;
	argv = *argv_p;
	here_doc = (ft_strcmp(argv[1], "here_doc") == 0);
	if (here_doc)
		io[0] = get_here_doc_input(argv[2]);
	else if (find_file_in_env(argv[1], NULL, &fn, R_OK))
		io[0] = open(fn, O_RDONLY);
	else
		return (PPX_ERROR("Input file not found or read permission denied.",
				EXIT_INPUT_FILE_ERR));
	malloc_free_p(0, (void **)&fn);
	if (io[0] < 0)
		return (PPX_ERROR("Input file open call failed.", EXIT_INPUT_OPEN_ERR));
	if (find_file_in_env(argv[*argc - 1], NULL, &fn, 0) && access(fn, W_OK) < 0)
		return (clear_ppx(ppx, &fn, EXIT_OUTPUT_FILE_ERR));
	if (here_doc)
		io[1] = open(argv[*argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		io[1] = open(argv[*argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	malloc_free_p(0, (void **)&fn);
	if (io[1] < 0)
		return (clear_ppx(ppx, &fn, EXIT_OUTPUT_OPEN_ERR));
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
	int		valid_code;

	if (argc < 5 || argc > CMD_MAX)
		return (PPX_ERROR("Pipex takes from 4-64 arguments.",
				EXIT_WRONG_NB_INPUTS));
	printf("PIPE_RD, PIPE_WR : %d, %d\n", PIPE_RD, PIPE_WR);
	ft_memclear(&ppx, sizeof(t_ppx));
	valid_code = validate_io_files(&ppx, &argc, &argv);
	if (valid_code < 0)
		return (valid_code);
	valid_code = parse_validate_cmds(&ppx, argc, argv, env);
	if (valid_code < 0)
		return (valid_code);
	print_cmds(&ppx);
	valid_code = exec_cmd_chain(&ppx, env);
	return (clear_ppx(&ppx, NULL, EXIT_SUCCESS));
}
