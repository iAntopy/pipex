/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 22:40:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/02 22:08:31 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_pipe(int *pp_rd)
{
	int		pp[2];
	char	buff[4096];
	ssize_t	nchrs;

	pipe(pp);
	nchrs = read(*pp_rd, buff, 4096);
	buff[nchrs] = '\0';
	printf("Pipe content : \n");
	printf("%s", buff);
	write(pp[1], buff, nchrs);
	close(*pp_rd);
	close(pp[1]);
	*pp_rd = pp[0];
}

// returns read side of a pipe filled with user input.
int	get_here_doc_input(char *limiter)
{
	int		pp[2];
	char	buff[HDOC_SIZE];
	ssize_t	nchrs;

	if (pipe(pp) < 0)
		return (-1);
	while (1)
	{
		ft_printf("pipe heredoc> ");
		nchrs = read(0, buff, HDOC_SIZE);
		if (nchrs < 0)
			return (-1);
		if (strncmp(buff, limiter, nchrs - 1) == 0)
			break ;
		write(pp[1], buff, nchrs);
	}
	close(pp[1]);
	print_pipe(pp);
	return (pp[0]);
}
