/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:19:58 by iamongeo          #+#    #+#             */
/*   Updated: 2022/09/21 22:01:33 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# include "libft.h"

# ifndef CMD_MAX
#  define CMD_MAX 2
# endif
# define HDOC_SIZE 4096

typedef struct s_pipex_super_struct
{
	int		nb_cmds;
	char	**paths;
	int		io[2];
	int		pp[2];
	int		pids[CMD_MAX + 1];
	char	**argv;
	int		*in;
	int		rd_pipe;
	int		*out;
}	t_ppx;

enum	e_exit_codes
{
	ENOCMD = 127
};

///// GENERIC UTILS ///////
int		close_pipe(int *rd, int *wr);
int		init_pipe(t_ppx *ppx, int i);

///// VALIDATOR FUNCS ///////
int		parse_validate_cmd(char **paths, char *cmd, char ***ret_argv);
int		validate_io_files(int *io, int argc, char **argv_p, int here_doc);
int		validate_pipex_input_args(int argc, char **argv, int *here_doc);

///// BONUS INPUT FUNC //////
int		get_here_doc_input(char *limiter, int n_cmds);

///// ERROR_HANDLING /////
int		repport_bad_inputs(int argc);
int		repport_error(char *err);
int		repport_file_error(char *filename);
int		repport_bad_cmd(char ***argv, char **filename);
int		repport_execve_failed(char *cmd);
//int		repport_excessive_cmds(int argc, int here_doc);
//int		repport_cmd_exec_failure(char *cmd, int status);

#endif
