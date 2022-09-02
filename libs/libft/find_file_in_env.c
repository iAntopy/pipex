/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file_in_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 01:13:38 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/02 15:45:47 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	**get_env_paths(char **env)
{
	env--;
	while (*(++env))
		if (ft_strncmp(*env, "PATH", 4) == 0 && (*env)[4] == '=')
			break ;
	if (!(*env))
		return (NULL);
	return (ft_split(*env + 5, ':'));
}

int	find_file_in_paths(char *filename, char **paths, char **found_path, int mode)
{
	char	fn[FILENAME_MAX];
	char	acc_path[PATH_MAX];

	if (!paths || !filename)
		return (0);
	*found_path = NULL;
	if (filename[0] != '/')
	{
		fn[0] = '/';
		ft_strlcpy(fn + 1, filename, FILENAME_MAX);
	}
	else
		ft_strlcpy(fn, filename, FILENAME_MAX);
	while (*paths)
	{
		ft_strlcpy(acc_path, *paths, PATH_MAX);
		ft_strlcat(acc_path, fn, PATH_MAX);
		if (access(acc_path, F_OK | mode) == 0)
			break ;
		paths++;
	}
	if (*paths == NULL)
		return (0);
	*found_path = ft_strdup(acc_path);
	return (1);
}

// acc_path (access path) is the resulting full path of the file found in env
// if and only if function call returns 1. If 0 is returned file was not found. 
static int	search_file_in_env(char *filename, char **env, char *acc_path)
{
	char	**tab;
	char	**t;
	int		file_found;

	tab = get_env_paths(env);
	if (!tab)
		return (0);
	t = tab - 1;
	while (*(++t))
	{
		ft_strlcpy(acc_path, *t, PATH_MAX);
		ft_strlcat(acc_path, filename, PATH_MAX);
		if (access(acc_path, F_OK) == 0)
			break ;
	}
	file_found = (*t != NULL);
	strtab_clear(&tab);
	return (file_found);
}

int	find_exe_in_env(char *filename, char **env, char **found_path)
{
	char	fn[FILENAME_MAX];
	char	path[PATH_MAX];
	char	*f;

	if (!filename || !found_path)
	{
		fperror("Missing parameters to %s\n", __FUNCTION__);
		return (0);
	}
	*found_path = NULL;
	f = fn;
	if (filename[0] != '/')
		*(f++) = '/';
	ft_strlcpy(f, filename, sizeof(fn) - 1);
	if (access(filename, F_OK | X_OK) == 0)
	{
		getcwd(path, sizeof(path));
		ft_strlcat(path, fn, sizeof(path));
	}
	else if (!env || !search_file_in_env(fn, env, path) || (access(path, X_OK) < 0))
		return (0);
	*found_path = ft_strdup(path);
	return (1);
}

// mode is bitwise ORed access mode flags. Either or both R_OK, W_OK.
int	find_file_in_env(char *filename, char **env, char **found_path, int mode)
{
	char	fn[FILENAME_MAX];
	char	path[PATH_MAX];

	if (!filename || !found_path)
	{
		fperror("Missing parameters to %s\n", __FUNCTION__);
		return (0);
	}
	*found_path = NULL;
	if (filename[0] != '/')
		fn[0] = '/';
	ft_strlcpy(fn + (filename[0] != '/'), filename, sizeof(fn));
	if (access(filename, F_OK | mode) == 0)
	{
		getcwd(path, sizeof(path));
		ft_strlcat(path, fn, sizeof(path));
	}
	else if (!env || !search_file_in_env(fn, env, path) || access(path, mode) < 0)
		return (0);
	*found_path = ft_strdup(path);
	return (1);
}
