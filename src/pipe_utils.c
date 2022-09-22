/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:46:17 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/21 21:47:44 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	close_pipe(int *rd, int *wr)
{
	if (rd && *rd >= 3)
	{
		close(*rd);
		*rd = -1;
	}
	if (wr && *wr >= 3)
	{
		close(*wr);
		*wr = -1;
	}
	return (0);
}

int	init_pipe(t_ppx *ppx, int i)
{
	int	is_first;
	int	is_last;

	is_first = (i == 0);
	is_last = (i == (ppx->nb_cmds - 1));
	ppx->in = &ppx->rd_pipe;
	ppx->out = ppx->pp + 1;
	if (!is_last && (pipe(ppx->pp) < 0))
		return (repport_error("pipe call failed"));
	if (is_first)
		ppx->in = ppx->io;
	else if (is_last)
	{
		ppx->pp[0] = -1;
		ppx->out = ppx->io + 1;
	}
	return (0);
}
