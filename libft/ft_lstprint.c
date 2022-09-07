/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:41 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/01 21:57:53 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint_int(t_list *lst)
{
	ft_putstr("[ ");
	while (lst)
	{
		ft_putnbr(*(int *)(lst->content));
		write(1, ", ", 2 * (lst->next != NULL));
		lst = lst->next;
	}
	ft_putstr(" ]");
}

void	ft_lstprint_str(t_list *lst)
{
	ft_putstr("[ ");
	while (lst)
	{
		ft_putstr(*(char **)(lst->content));
		write(1, ", ", 2 * (lst->next != NULL));
		lst = lst->next;
	}
	ft_putstr(" ]");
}

/*
void	ft_lstprint_float(t_list *lst)
{
	ft_putstr("[ ");
	while (lst)
	{
		ft_putstr(*(float *)(lst->content));
		write(1, ", ", 2 * (lst->next != NULL));
		lst = lst->next;
	}
	ft_putstr(" ]");
}
*/

/* LINKED INTS LIST
int	main(void)
{
	t_list	*lst;
	int	i;

	lst = NULL;
	i = 0;
	ft_putnbr(10);
	write(1, "\n", 1);
	while (i < 20)
	{
		ft_lstadd_back(&lst, ft_lstcreate(&i, sizeof(int)));
		i++;
	}
	ft_lstprint_int(lst);
	return (0);
}
*/
/*
// LINKED STRS LIST
int	main(int argc, char *argv[])
{
	t_list	*lst;
	int	i;

	lst = NULL;
	i = 0;
	while (i < (argc - 1))
	{
		ft_lstadd_back(&lst, ft_lstcreate(&argv[i + 1], sizeof(char *)));
		i++;
	}
	ft_lstprint_str(lst);
	return (0);
}
*/
