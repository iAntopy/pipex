/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 19:01:29 by iamongeo          #+#    #+#             */
/*   Updated: 2022/08/30 01:48:08 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Looks for a section of a string representing a substring to a longer str.
// eg. :  "cut -d' ' -f1" or "grep 'This is not a drill !'"
// These sub-strings are allowed to hold space chars and should not be 
// split with ft_split_space. If a substr exists, the space characters inside
// will be substituted by one of the chars defined by SUBSTR_SUBST_CHARS 
// (whichever first is found to not appear in the substr itself).
// This substitution happens before ft_split_space so that the substr stays 
// complet. The char used for substitution will be kept for restoring these 
// chars to space chars post ft_split_space.

static char	find_suitable_subst_char(char *str)
{
	char	*sc;

	sc = SPACE_SUBST_CHARS - 1;
	while (*(++sc))//(SPACE_SUBST_CHARS[++i])
		if (!ft_strchr(str, *sc))//SPACE_SUBST_CHARS[i]))
			return (*sc);
	return (0);
}

/*
// strlen excluding char c.
static size_t	ft_strlen_xchr(const char *str, const char c)
{
	size_t	len;

	len = 0;
	while (*str)
		len += (*(str++) != c);
	return (len);
}
*/
char	substitute_spaces_in_substr(char *str)
{
	char	*cur;
	char	*sub;
	char	*sub2;
	char	sc;
	char	do_sub;

	sub = ft_strchr(str, '\'');
	sub2 = ft_strrchr(str, '\'');
	if (sub && sub2 != sub)
	{
		printf("SUBSTITUTION REQUIRED !\n");
		do_sub = 1;
		cur = sub;
		sc = find_suitable_subst_char(str);
		printf("found suitable subst char : %c (%d)\n", sc, (int)sc);
		while (++sub != sub2)
		{
			if (do_sub && *sub == ' ')
				*cur = sc;
			else
				*cur = *sub;
			if (*sub == '\'')
				do_sub = !do_sub;
			else
				cur++;
		}
		while (*(++sub2))
			*(cur++) = *sub2;
		*cur = '\0';
		printf("resulting substitution : %s\n", str);
		return (sc);
	}
	return (0);
}

void	restore_spaces_in_substr(char **tab, char sc)
{
	char	**t;
	char	*s;

	if (!sc)
		return ;
	t = tab;
	printf("SUBSTITUTION RESTORATION REQUIRED !\n");
	printf("tab pre restoration : \n");
	strtab_print(tab);
	while (*t)
	{
		s = *t - 1;
		while (*(++s))
			if (*s == sc)
				*s = ' ';
		t++;
	}
	printf("tab post restoration : \n");
	strtab_print(tab);
}
