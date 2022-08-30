/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/29 20:02:42 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clear_ppx(t_ppx *ppx, char **fn, int exit_code)
{
	char	***cmds;
	int	*io;

	cmds = ppx->cmd_args;
	io = ppx->io_fds;
	while (*cmds)
		strtab_clear(cmds++);
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

int	validate_io_files(t_ppx *ppx, int argc, char **argv)
{
	char	*filename;
	int	*io;

	io = ppx->io_fds;
	if (!find_file_in_env(argv[1], NULL, &filename, R_OK))
		return (PPX_ERROR("Input file not found or read permission denied.", EXIT_INPUT_FILE_ERR));
	io[0] = open(filename, O_RDONLY);
	malloc_free_p(0, (void **)&filename);
	if (io[0] < 0)
		return (PPX_ERROR("Input file open call failed.", EXIT_INPUT_OPEN_ERR));
	if (find_file_in_env(argv[argc - 1], NULL, &filename, 0) && access(filename, W_OK) < 0)
		return (clear_ppx(ppx, &filename, EXIT_OUTPUT_FILE_ERR));
	io[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	malloc_free_p(0, (void **)&filename);
	if (io[1] < 0)
		return (clear_ppx(ppx, &filename, EXIT_OUTPUT_OPEN_ERR));
	return (0);
}

int	parse_validate_cmds(t_ppx *ppx, int argc, char **argv, char **env)
{
	int	i;
	char	***cmds;
	char	*filename;

	cmds = ppx->cmd_args;
	i = -1;
	while (++i < argc)
	{
//		printf("checking argv[%d] = %s\n", i, argv[i]);
		ppx->sc = substitute_spaces_in_substr(argv[i]);
		cmds[i] = ft_split_space(argv[i]);
		restore_spaces_in_substr(cmds[i], ppx->sc);
//		printf("split DONE\n");
		if (!find_exe_in_env(cmds[i][0], env, &filename))
		{
			fperror(RED_BC"<[ Pipex ERROR : %s : No command named %s ]>"WHITE_C,
				 __FUNCTION__, cmds[i][0]);
			return (clear_ppx(ppx, &filename, EXIT_INVALID_CMD));
		}
//		printf("find exe DONE : %s\n", filename);
		malloc_free_p(0, (void **)&cmds[i][0]);
		cmds[i][0] = filename;		
	}
	ppx->nb_cmds = i;
	return (0);
}

void	print_cmds(t_ppx *ppx)
{
	char 	***cmds;

	cmds = ppx->cmd_args;
	while (*cmds)
		strtab_print(*(cmds++));
}

int	main(int argc, char **argv, char **env)
{
	t_ppx	ppx;
//	char	**cmd_argvs[CMD_MAX];
//	int	io_fds[2];
	int	valid_code;

	if (argc < 5 || argc > CMD_MAX)
		return (PPX_ERROR("Pipex takes from 4-64 arguments.", 
				EXIT_WRONG_NB_INPUTS));

	printf("PIPE_RD, PIPE_WR : %d, %d\n", PIPE_RD, PIPE_WR);
	ft_memclear(&ppx, sizeof(t_ppx));
	valid_code = validate_io_files(&ppx, argc, argv);
	if (valid_code < 0)
		return (valid_code);
//	printf("About to validate cmds\n");	
	valid_code = parse_validate_cmds(&ppx, argc - 3, argv + 2, env);
	if (valid_code < 0)
		return (valid_code);
//	printf("DONE validate cmds\n");	
//	printf("About to print cmds\n");	
	print_cmds(&ppx);
	valid_code = exec_cmd_chain(&ppx, env);
//	printf("DONE print cmds\n");	
	return (clear_ppx(&ppx, NULL, EXIT_SUCCESS));
}
