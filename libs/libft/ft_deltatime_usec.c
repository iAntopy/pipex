/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltatime_usec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:10:46 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/10 20:15:44 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/time.h>

static void	ft_put_delta_t(ssize_t d, char *note)
{
	ssize_t	secs;
	ssize_t	ms;
	ssize_t	us;

	secs = d / 1000000;
	ms = (d % 1000000) / 1000;
	us = (d % 1000);
	ft_printf("%ld sec, %ld ms and %ld usec elapsed : %s\n", secs, ms, us, note);
}

ssize_t	ft_deltatime_usec_note(char *note)
{
	static struct timeval	last_t;
	struct timeval			curr_t;
	ssize_t					delta_t;

	gettimeofday(&curr_t, NULL);
	if (last_t.tv_sec)
	{
		delta_t = (size_t)(curr_t.tv_sec - last_t.tv_sec) * 1000000;
		delta_t += (size_t)(curr_t.tv_usec - last_t.tv_usec);
		if (note)
			ft_put_delta_t(delta_t, note);
	}
	else
		delta_t = 0;
	last_t.tv_sec = curr_t.tv_sec;
	last_t.tv_usec = curr_t.tv_usec;
	return (delta_t);
}

ssize_t	ft_deltatime_usec(void)
{
	static struct timeval	last_t;
	struct timeval			curr_t;
	ssize_t					delta_t;

	gettimeofday(&curr_t, NULL);
	if (last_t.tv_sec)
	{
		delta_t = (size_t)(curr_t.tv_sec - last_t.tv_sec) * 1000000;
		delta_t += (size_t)(curr_t.tv_usec - last_t.tv_usec);
	}
	else
		delta_t = 0;
	last_t = curr_t;
	return (delta_t);
}
/*
int	main()
{
	size_t	delta_t;

	ft_time_delta_usec(0);
	sleep(1);
	delta_t = ft_time_delta_usec(1);
	return (0);
}
*/
