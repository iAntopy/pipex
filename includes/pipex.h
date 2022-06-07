
#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

# include <stdio.h>
# include "libft.h"

typedef struct s_exe_pkg
{
	struct s_exe_pkg	*next;
	char				**argv;
	int					rd;
	int					wt;
} t_exe_p;

void	clr_str_tab(char **tab);
char	**get_paths_table(char **env);
int	search_file_in_env(char *file, char **paths, char **ret);
char	*parse_full_path(char *env_path, char *file);


//////// ERROR HANDLING /////////
int	perror_ENOENT();
int	perror_EACCES();

#endif
