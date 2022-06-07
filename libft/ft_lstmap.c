/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:48:57 by iamongeo          #+#    #+#             */
/*   Updated: 2022/03/28 16:26:08 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*crs;

	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	crs = new;
	while (lst->next)
	{
		lst = lst->next;
		crs->next = ft_lstnew(f(lst->content));
		if (!(crs->next))
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		crs = crs->next;
	}
	return (new);
}
