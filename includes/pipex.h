/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:19:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/02 15:20:13 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

# include "libft.h"

# define CMD_MAX 64
# define PIPE_RD 001
# define PIPE_WR 010
# define SPACE_SUBST_CHARS "~?&#@!|<>"
# define HDOC_SIZE 4096

# define PPX_ERROR(err, code) report_error((err), __FUNCTION__, (code))

typedef struct s_pipex_super_struct
{
	int	nb_cmds;
	char	**cmd_args[CMD_MAX];
	char	**paths;
	int	io_fds[2];
	char	sc;
}	t_ppx;

enum	e_exit_codes
{
	EXIT_WRONG_NB_INPUTS = -42,
	EXIT_INPUT_FILE_ERR,
	EXIT_INPUT_OPEN_ERR,
	EXIT_OUTPUT_FILE_ERR,
	EXIT_OUTPUT_OPEN_ERR,
	EXIT_INVALID_CMD,
	EXIT_PIPE_ERR,
	EXIT_FORK_ERR,
	EXIT_CMD_EXEC_ERR
};

int	exec_cmd_chain(t_ppx *ppx, char **env);
int	get_here_doc_input(char *limiter);
void	print_pipe(int *pp_rd);

///// SUBSTITUTION TOOLS /////
char	substitute_spaces_in_substr(char *str);
void	restore_spaces_in_substr(char **tab, char sc);


///// ERROR_HANDLING /////
int	report_error(char *err, const char *func_name, int exit_code);
int	report_child_exec_err(char *cmd, int status);

#endif
