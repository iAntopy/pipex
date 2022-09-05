/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:40:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/04 03:43:12 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			return (-1);
		if (strncmp(buff, limiter, nchrs - 1) == 0)
			break ;
		write(pp[1], buff, nchrs);
	}
	close(pp[1]);
	return (pp[0]);
}
