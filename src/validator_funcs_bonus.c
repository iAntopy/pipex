/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_funcs_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 21:50:28 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/10 06:19:31 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	validate_pipex_input_args(int argc, char **argv, int *here_doc)
{
	if (argc < 2)
		return (repport_bad_inputs(argc));
	*here_doc = (ft_strcmp("here_doc", argv[1]) == 0);
	argc -= *here_doc;
	if ((argc < 5) || ((argc - 3) > CMD_MAX))
		return (repport_bad_inputs(argc + *here_doc));
	return (0);
}

int	validate_io_files(int *io, int argc, char **argv, int here_doc)
{
	int	pp[2];

	if (here_doc)
		io[0] = get_here_doc_input(argv[2], argc - 5);
	else if (access(argv[1], F_OK | R_OK) < 0)
	{
		if (pipe(pp) < 0)
			return (repport_error("pipe failed"));
		io[0] = pp[0];
		close_pipe(NULL, pp + 1);
		repport_file_error(argv[1]);
	}
	else
		io[0] = open(argv[1], O_RDONLY);
	if (io[0] < 0)
		repport_file_error(argv[1]);
	if (io[0] == 0)
		return (-1);
	if (access(argv[argc - 1], F_OK) == 0 && access(argv[argc - 1], W_OK) < 0)
		return (repport_file_error(argv[argc - 1]));
	io[1] = open(argv[argc - 1], O_CREAT | O_WRONLY
			| (O_TRUNC + here_doc * (O_APPEND - O_TRUNC)), 0644);
	if (io[1] < 0)
		return (repport_file_error(argv[argc - 1]));
	return (0);
}

int	parse_validate_cmd(char	**paths, char *cmd, char ***ret_argv)
{
	char	*filename;
	char	**argv;
	char	sc;

	sc = substitute_spaces_in_substr(cmd);
	*ret_argv = NULL;
	argv = ft_split_space(cmd);
	if (!argv)
		return (repport_error("malloc failed on split"));
	restore_spaces_in_substr(argv, sc);
	if (!find_file_in_paths(argv[0], paths, &filename, F_OK)
		|| access(filename, X_OK) < 0)
		return (repport_bad_cmd(&argv, &filename));
	malloc_free_p(0, (void **)&argv[0]);
	argv[0] = filename;
	*ret_argv = argv;
	return (0);
}
