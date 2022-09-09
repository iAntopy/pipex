/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:19:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/09 05:29:33 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# include "libft.h"

# define SPACE_SUBST_CHARS "~?&#@!|<>-+%"
# define HDOC_SIZE 4096

typedef struct s_pipex_super_struct
{
	int		nb_cmds;
	char	**cmd_args[CMD_MAX + 1];
	char	**paths;
	int		io[2];
	int		pids[CMD_MAX + 1];
	char	sc;
}	t_ppx;

enum	e_err_codes
{
	ERR_OCCURED = -1,
	EXIT_CMD_NOT_FOUND,
	EXIT_CMD_NOT_EXE
};

enum	e_pipe_masks
{
	PIPE_RD = 001,
	PIPE_WR = 010
};

///// GENERIC UTILS ///////
void	close_pipe(int pp[2], int close_mask);

///// VALIDATOR FUNCS ///////
int		parse_validate_cmds(t_ppx *ppx, int argc, char **argv, char **env);
int		validate_io_files(t_ppx *ppx, int *argc, char ***argv_p, int here_doc);
int		validate_pipex_input_args(int argc, char **argv, int *here_doc);

///// BONUS INPUT FUNC //////
int		get_here_doc_input(char *limiter, int n_cmds);

///// SUBSTITUTION TOOLS //////
char	substitute_spaces_in_substr(char *str);
void	restore_spaces_in_substr(char **tab, char sc);

///// ERROR_HANDLING /////
int		repport_bad_inputs(int argc);
int		repport_error(char *err);
int		repport_bad_cmd(char *cmd, int status);
int		repport_excessive_cmds(int argc, int here_doc);
int		repport_cmd_exec_failure(char *cmd, int status);
//int		check_cmd_exec_err(char *cmd, int status, int pp[2], int pid);

#endif
