/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:47:19 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/13 18:48:39 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = cur->next;
		ft_lstdelone(cur, del);
	}
	*lst = NULL;
}
