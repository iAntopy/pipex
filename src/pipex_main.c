/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:14:24 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/07 19:38:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clear_ppx(t_ppx *ppx, int err_occured)
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
	return (err_occured);
}

void	print_cmds(char ***cmds)
{
	cmds--;
	while (*(++cmds))
		strtab_print(*cmds);
}

int	main(int argc, char **argv, char **env)
{
	t_ppx	ppx;
	int		here_doc;

	ft_memclear(&ppx, sizeof(t_ppx));
	if (validate_pipex_input_args(argc, argv, &here_doc) < 0)
		return (errno);
	if (validate_io_files(&ppx, &argc, &argv, here_doc) < 0)
		return (errno);
	if (parse_validate_cmds(&ppx, argc, argv, env) < 0)
		return (errno);
	if (exec_cmd_chain(&ppx, env) < 0)
		return (errno);
	return (clear_ppx(&ppx, !ERR_OCCURED));
}
