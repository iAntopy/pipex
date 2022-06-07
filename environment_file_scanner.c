
#include "libft.h"
#include "pipex.h"

//char	**ft_split(const char *str, char c);

char	**get_paths_table(char **env)
{
	char	*s;
	char	*p;


	s = *(env++);
	p = NULL;
	while (!p && s)
	{
		if (s[0] == 'P' && s[1] == 'A' && s[2] == 'T' && s[3] == 'H')
			p = s + 5;
		s = *(env++);
	}
	if (p)
		return (ft_split((const char *)p, ':'));
	return (NULL);
}

void	clr_str_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

size_t	ft_tablen(const char **tab, int	*tablen)
{
	int	i;
	size_t	len;

	i = -1;
	len = 0;
	while (tab[++i])
		len += ft_strlen(tab[i]);
	*tablen += i;
	return (len);
}

static char	*copy_path_tab(char *path, char **tab)
{
	char	*t;
	char	*p;

	p = path;
	while (*tab)
	{
		t = *(tab++);
		printf("copying tab %s\n", t);
		*(p++) = '/';
		while (*t)
			*(p++) = *(t++);
	}
	return (p);
}

static char	*ft_join_path_tabs(char **tab1, char **tab2)
{
	size_t	total_len;
	int	n_tab_elems;
	char	*path;
	char	*p;

	n_tab_elems = 0;
	total_len = 0;
	total_len += ft_tablen((const char **)tab1, &n_tab_elems);
	total_len += ft_tablen((const char **)tab2, &n_tab_elems);
	printf("tablens gathered : total %zu, n_tabs %d\n", total_len, n_tab_elems);
	path = (char *)malloc(sizeof(char) * (n_tab_elems + total_len + 1));
	if (!path)
		return (NULL);
	printf("Copy start\n");
	p = copy_path_tab(path, tab1);
	p = copy_path_tab(p, tab2);
	printf("Copy DONE\n");
	*p = '\0';
	return (path);
}

char	*parse_full_path(char *env_path, char *file)
{
	char	*path;
	char	*p;
	size_t	total_len;

	if (!env_path || !file)
		return (NULL);
	total_len = 0;
	total_len += ft_strlen(env_path);
	total_len += ft_strlen(file);
	path = (char *)malloc(sizeof(char) * (total_len + 2));
	if (!path)
		return (NULL);
	p = path;
	while (*env_path)
		*(p++) = *(env_path++);
	*(p++) = '/';
	while (*file)
		*(p++) = *(file++);
	*p = '\0';
	return (path); 
}

/*
char	*ft_join(char *s1, char *s2)
{
	char	*str;
	char	*s;
	int	len;

	if (!s1 || !s2)
		return (NULL);
	len = 0;
	s = s1;
	while (*s)
		len++;
	s = s2;
	while (*s)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	s = str;
	while (*s1)
		*(s++) = *(s1++);
	while (*s2)
		*(s++) = *(s2++);	
	*s = '\0';
	return (str);	
}
*/
int	search_file_in_env(char *file, char **paths, char **ret)
{
	int	i;
	char	*full_path;

	printf("Starting search for valid path. \n");
	if (!file || !paths)
		return (0);
	i = -1;
	*ret = NULL;
	if (access(file, F_OK) == 0)
		*ret = ft_strdup(file);
	if (!(*ret))
		return (-1);
	while (!(*ret) && paths[++i])
	{
		*ret = parse_full_path(paths[i], file);
		if (!(*ret))
			return (-1);
		else if (access(*ret, F_OK) == 0)
			break ;
		free(*ret);
		*ret = NULL;
	}
	return (*ret != NULL);
}
