/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substring_substitution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:45:15 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/21 18:21:55 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	find_suitable_subst_char(char *str)
{
	const char	sp_chrs[] = "#?*!@+-=0123456789";
	int			i;

	i = -1;
	while (sp_chrs[++i])
		if (!ft_strchr(str, sp_chrs[i]))
			return (sp_chrs[i]);
	return (0);
}

static char	*find_substring(char *str)
{
	char	*p1;
	char	*p2;

	if (!str)
		return (NULL);
	while (*str)
	{
		p1 = ft_strchr_set(str, "\'\"");
		if (!p1)
			return (NULL);
		p2 = ft_strchr(p1 + 1, *p1);
		if (!p2)
			str = p1 + 1;
		else
			return (p1);
	}
	return (NULL);
}

char	substring_substitution(char *str, char	**subst)
{
	char	sc;
	char	dlim;
	char	*sub;

	if (!str || !subst)
		return (0);
	sc = find_suitable_subst_char(str);
	sub = find_substring(str);
	if (!sc || !sub)
		return (0);
	*subst = ft_strdup(str);
	if (!(*subst))
		return (0);
	sub = *subst + (sub - str);
	while (sub)
	{
		dlim = *sub;
		while (*(++sub) != dlim)
			*(sub - 1) = *sub + ((*sub == ' ') * (sc - *sub));
		ft_memmove(sub - 1, sub + 1, ft_strlen(sub + 1) + 1);
		sub = find_substring(sub - 1);
	}
	return (sc);
}

void	restore_substring(char *str, char sc)
{
	if (!str)
		return ;
	str--;
	while (*(++str))
		if (*str == sc)
			*str = ' ';
}

void	restore_substrings_in_tab(char **tab, char sc)
{
	if (!tab || !(*tab))
		return ;
	while (*tab)
		restore_substring(*(tab++), sc);
}
/*
int	main()
{
	char	str[] = "Ceci est une 'quote de fou' ! \"Incoyable ce truc de oof             \" !";
	char	*subst;
	char	sc;
	char	**tab;
	
	sc = substring_substitution(str, &subst);
	ft_printf("Final string after substitution : %s\n", str);
	tab = ft_split(subst, ' ');
	ft_printf("tab after substring substitution : \n");
	strtab_print(tab);
	restore_substrings_in_tab(tab, sc);
	ft_printf("tab after subtring recovery : \n");
	strtab_print(tab);
	ft_printf("Original str : %s\n", str);
	ft_printf("Substituted str : %s\n", subst);
	return (0);
}
*/
