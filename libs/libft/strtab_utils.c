/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 04:23:34 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/05 17:34:25 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Utility functions for tabs of char pointers. eg: str tab from ft_split

int	strtab_len(char **tab)
{
	int	i;

	i = 0;
	while (*(tab++))
		i++;
	return (i);
}

void	strtab_clear(char ***tab)
{
	char	**t;

	t = *tab;
	t--;
	while (*(++t))
		malloc_free_p(0, (void **)t);
	malloc_free_p(0, (void **)tab);
}

void	strtab_swap(char **tab, int index1, int index2)
{
	int		len;
	char	*temp;

	len = strtab_len(tab);
	if (index1 < 0 || len <= index1 || index2 < 0 || len <= index2)
		return ;
	temp = tab[index1];
	tab[index1] = tab[index2];
	tab[index2] = temp;
}

void	strtab_print(char **tab)
{
	int	i;

	if (!tab)
	{
		fperror("libft : %s : missing argument {tab}\n", __FUNCTION__);
		return ;
	}
	i = 1;
	ft_printf("\n@----------String Table-----------@\n");
	while (*tab)
	{
		ft_printf("| %d - %s$\n", i, *tab);
		i++;
		tab++;
	}
	ft_printf("@---------------@@@--------------@\n");
}
