/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:46:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/13 19:10:02 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstinsert(t_list **lst, unsigned int index, t_list *new)
{
	t_list	*elem;

	if (index == 0)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
	elem = *lst;
	while (--index && elem->next)
		elem = elem->next;
	if (index == 0)
	{
		new->next = elem->next;
		elem->next = new;
	}
	else
		return (0);
	return (1);
}
/*
int	main(int argc, char *argv[])
{
	t_list	*lst;
	t_list	*elem;
	int	i;
	char	str[] = "AAAAAA";
	char	*dup;

	lst = NULL;
	i = 0;
	dup = ft_strdup(str);
	elem = ft_lstnew(&dup);
	if (argc > 1)
	{
		ft_putstr("JE SUIS ICI !\n");
		while (++i < argc)
			ft_lstadd_back(&lst, ft_lstcreate(argv + i, sizeof(char *)));
		ft_lstprint_str(lst);
		ft_lstinsert(&lst, 6, elem);
		ft_lstprint_str(lst);

	}
	return (0);
}
*/
