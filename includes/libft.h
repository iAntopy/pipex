/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:20:53 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/07 19:44:02 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BLACK_C	"\033[0;30m"
# define RED_C		"\033[0;31m"
# define GREEN_C	"\033[0;32m"
# define YELLOW_C	"\033[0;33m"
# define BLUE_C		"\033[0;34m"
# define PURPLE_C	"\033[0;35m"
# define CYAN_C		"\033[0;36m"
# define WHITE_C	"\033[0;37m"

# define BLACK_BC	"\033[1;30m"
# define RED_BC		"\033[1;31m"
# define GREEN_BC	"\033[1;32m"
# define YELLOW_BC	"\033[1;33m"
# define BLUE_BC	"\033[1;34m"
# define PURPLE_BC	"\033[1;35m"
# define CYAN_BC	"\033[1;36m"
# define WHITE_BC	"\033[1;37m"

# ifndef SIZE_MAX
#  define SIZE_MAX 0xffffffffffffffff
# endif

# define X_BASE "0123456789abcdef"
# define XX_BASE "0123456789ABCDEF"
# define DEC_BASE "0123456789"

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
//# include <stdio.h>

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
char	*ft_strstr(const char *s1, const char *s2);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_atoi_base(const char *str, int base, const char *base_str);
void	*ft_calloc(size_t nmemb, size_t size);

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_issign(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
void	ft_memclear(void *dest, size_t size);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	**ft_split_set(char const *s, char *set);
char	**ft_split_space(char const *s);
char	*ft_itoa(int n);
double	ft_atof(const char *str);
int		ft_pow(int nb, int exp);
char	*ft_strlower(char *str);
char	*ft_strupper(char *str);

void	ft_putchar(int c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putbin(const void *addr, size_t n);

void	ft_swap_i(int *a, int *b);
void	ft_swap_f(float *a, float *b);
int		ft_clamp(int n, int min, int max);

void	fperror(char *fmt, ...);
ssize_t	ft_deltatime_usec(void);
ssize_t	ft_deltatime_usec_note(char *note);
float	ft_random(void);
int		ft_randint(int min, int range);

int		malloc_free_p(size_t size, void **ptr);
void	*malloc_free(size_t size, void **ptr);

////////////// FILE SEARCH FUNCtIONS ////////////////
// Search functions to find files in environment paths or cwd.
//	- filename :	name of file to look for.
//	- env :		env variable from main. If NULL acts as
//			the access function in pwd.
//	- found_path :	a ptr to a (char *) variable declared 
//			externaly. if func returns 1, this variable
//			will be a ptr to a malloced str with the full path
//			to the file requested.
//	- mode :	access flags to check access permissions.
//			Either R_OK or W_OK or bitwise OR of both (R_OK | W_OK).

int		find_file_in_env(char *fname, char **env, char **acc_path, int mode);
int		find_exe_in_env(char *fname, char **env, char **acc_path);
char	**get_env_paths(char **env);
int		find_file_in_paths(char *fname, char **paths, char **acc_path,
			int mode);

/// STR TAB UTILS /// for malloced char ptr tabs such as ft_split returned tab.
int		strtab_len(char **tab);
void	strtab_clear(char ***tab);	// takes ptr to strtab
void	strtab_swap(char **tab, int index1, int index2);
void	strtab_print(char **tab);

/////// GET_NEXT_LINE ////////
# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 4096
# endif

typedef struct s_gdl
{
	struct s_gdl	*prev;
	struct s_gdl	*next;
	char			*str;
	size_t			n;
}	t_gdl;

enum	e_fail_codes
{
	E_EOF = SIZE_MAX - 2,
	E_MLC = SIZE_MAX - 1,
	E_IFD = SIZE_MAX
};

char	*get_next_line(int fd);
int		get_substr(char *str, size_t start, size_t n, char **ret);
int		gdl_insert(t_gdl **dlst, t_gdl **elem, char *str, size_t push_app);
int		join_clear_list(char *line, t_gdl **elem);
char	*gather_line(t_gdl **chks);
////////////////////////////////

////////// FT_PRINTF ///////////
int		ft_printf(const char *fmt, ...);
int		ft_vprintf(const char *fmt, va_list *ap);
/////////////////////////////////

/////// SINGLE LINKED LIST FUNCTIONS ////////
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstcreate(void *content, size_t size_of);
int		ft_lstinsert(t_list **lst, unsigned int index, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_lstpop(t_list **lst, unsigned int index);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstprint_int(t_list *lst);
void	ft_lstprint_str(t_list *lst);
void	ft_lstprint_float(t_list *lst);
///////////////////////////////////////////

#endif
