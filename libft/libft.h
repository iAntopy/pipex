/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:20:53 by iamongeo          #+#    #+#             */
/*   Updated: 2022/04/14 19:23:11 by iamongeo         ###   ########.fr       */
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

# define HEX_BASE_LOWERCASE "0123456789abcdef"
# define HEX_BASE_UPPERCASE "0123456789ABCDEF"

// homemade limits
# define CHAR_MAX 127
# define CHAR_MIN -128
# define SHRT_MAX 32767
# define SHRT_MIN -32768
# define USHRT_MAX 65535
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LONG_MAX 2147483647
# define LONG_MIN -2147483648
# define ULONG_MAX 4294967295U
# define LLONG_MAX 9223372036854775807LL
# define LLONG_MIN -9223372036854775808LL
# define ULLONG_MAX 18446744073709551615ULL
# define SIZE_MAX 18446744073709551615ULL

# include <unistd.h>
# include <stdlib.h>

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
int		ft_tolower(int c);
int		ft_toupper(int c);

void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
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
char	*ft_itoa(int n);

void	ft_putchar(int c);
void	ft_putstr(char const *s);
void	ft_putendl(char const *s);
void	ft_putnbr(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstcreate(void *content, size_t size_of);
void	ft_lstinsert(t_list **lst, unsigned int index, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
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

#endif
