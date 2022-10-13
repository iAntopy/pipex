/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:40:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/10/12 20:43:02 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	read_exception(int pp[2], int err_occured)
{
	close_pipe(pp, pp + 1);
	if (err_occured)
		fperror(RED_BC"<[PIPEX ERROR :: pipe call failed. ]>"WHITE_C);
	return (err_occured);
}

// returns read side of a pipe filled with user input.
int	get_here_doc_input(char *limiter, int n_pipes)
{
	int		i;
	int		pp[2];
	char	buff[HDOC_SIZE];
	ssize_t	nchrs;

	if (pipe(pp) < 0)
		return (-1);
	while (1)
	{
		i = -1;
		while (++i < n_pipes)
			ft_printf("pipe ");
		ft_printf("heredoc> ");
		nchrs = read(0, buff, HDOC_SIZE);
		if (nchrs < 0)
			return (read_exception(pp, 1));
		else if (nchrs == 0)
			return (read_exception(pp, 0));
		else if (nchrs > 1 && ft_strncmp(buff, limiter, nchrs - 1) == 0)
			break ;
		write(pp[1], buff, nchrs);
	}
	close_pipe(NULL, pp + 1);
	return (pp[0]);
}
