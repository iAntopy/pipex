#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

static const char in_file[] = "asdf";
static const char out_file[] = "fdsa";

typedef struct s_exe_pkg
{
	struct s_exe_pkg	*next;
	char				**argv;
	int					rd;
	int					wt;
} t_exe_p;

int	analyse_proc_exit(int wstatus)
{
	printf("~~~ EXIT ANALYST ~~~\n");
	if (!WIFEXITED(wstatus))
	{
		printf("~~~	Child process failed to execute with status : %d\n", wstatus);
		if (WIFSIGNALED(wstatus))
		{
			printf("~~~ Child process was signaled to exit\n");
			printf("~~~ Termination signal : %d\n", WTERMSIG(wstatus));
			printf("~~~ Process produced core dump : %s\n", WCOREDUMP(wstatus)?"TRUE":"FALSE");
		}
		if (WIFSTOPPED(wstatus))
			printf("~~~ Child process was stopped of signal (%d)\n", WSTOPSIG(wstatus));
		return (1);
	}
	printf("~~~	Child process exited correctely\n");
	return (0);
}

void	print_pipe_content(int *rd, int out)
{
	char	c;
	char	dummy;
	int		temp_file;
	size_t	n_chrs;
	char	buff[1000];

	temp_file = open("temp_f", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (temp_file < 0)
		return ;

	printf("allo 1\n");
	n_chrs = 1;
	while (n_chrs)
	{
		n_chrs = read(*rd, buff, 1000);
		write(temp_file, buff, 1000);
	}
	printf("allo 2\n");
	printf("Print pipe rd %d\n" , *rd);
	c = 0;
	write(out, "/// Pipe Content \\\\\\\n|| ", 25);
	close(temp_file);
	temp_file = open("temp_f", O_WRONLY);
	n_chrs = 1;
	printf("allo 3\n");
	while (n_chrs)
	{
		n_chrs = read(temp_file, buff, 1000);
		write(1, buff, n_chrs);
	}
	printf("allo 4\n");
	close(temp_file);
	*rd = open("temp_f", O_WRONLY);
	write(out, "\n\\\\\\ ------------ ///\n", 22);

/*
	while (c != dummy && --max_iter)
	{
		read(rd, &c, 1);
		if (c == '\n')
			write(out, "\n|| ", 4);
		else
			write(out, &c, 1);
		write(wt, &c, 1);
	}
	write(out, "\n\\\\\\ ------------ ///\n", 22);
	*rd = temp_file;
*/
}

int	append_exe_pkg(t_exe_p **x_lst, char **argv)
{
	t_exe_p	*xp;
	t_exe_p	*elem;

	if (!x_lst)
		return (-1);
	xp = (t_exe_p *)malloc(sizeof(t_exe_p));
	if (!xp)
		return (-1);
	xp->next = NULL;
	xp->argv = argv;
	xp->rd = -1;
	xp->wt = -1;
	if (*x_lst)
	{
		elem = *x_lst;
		while (elem->next)
			elem = elem->next;
		elem->next = xp;
	}
	else
		*x_lst = xp;
	return (0);
}

int	spawn_proc_exec(int *rd, int *wt, int rd2, char **argv, char **env)
{
	int	pid;
	int	wstatus;

	printf("Spawn start exec of prog %s with rd %d and wt %d\n", argv[0], *rd, *wt);
	wstatus = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		dup2(1, 99);
		dup2(*wt, 1);
		dup2(*rd, 0);
		if (execve(argv[0], argv, env) == -1)
			perror("Execution of program has failed");
		dup2(99, 1);
		printf("Child : Post %s exec failure. Attempting to close rd (%d) and wt (%d) files.\n", argv[0], *rd, *wt);
		close(*rd);
		close(*wt);
		printf("Child : rd and wt closed successfully\n");
		exit(1);
	}
	printf("Parent process waiting ...\n");
	close(*rd);
//	if (rd2)
//		print_pipe_content(rd2, *wt, 1);
	close(*wt);
	*rd = -1;
	*wt = -1;
	waitpid(pid, &wstatus, 0);
	printf("Parent process resumes.\n");
	return (wstatus);
}

int	lst_delone_xp(t_exe_p **xp, int close_rd)
{
	t_exe_p	*elem;

	if (!(xp && *xp))
		return (0);
	elem = *xp;
	if (close_rd && elem->rd != -1)
	{
		close(elem->rd);
		elem->rd = -1;
	}
	if (elem->wt != -1)
	{
		close(elem->wt);
		elem->wt = -1;
	}

	//free argv and its sub strings;
	*xp = elem->next;
	free(elem);
	return (0);
}

int	lst_clear(t_exe_p **xp)
{
	printf("LIST CLEAR !!!\n");
	while (xp && *xp)
		lst_delone_xp(xp, 1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	prog[] = "/bin/ls";
	char	prog1[] = "/bin/cat";
	char	prog2[] = "/usr/bin/grep";
	char	prog3[] = "/usr/bin/cut";
	char	*args[3] = {prog, "-la", NULL};
	char	*args1[3] = {prog1, "-e", NULL};
	char	*args2[3] = {prog2, "main", NULL};
	char	*args3[5] = {prog3, "-d", " ", "-f4-", NULL};
	t_exe_p	*x_lst = NULL;
	int		io_files[2];
	int		cur_rd;
	int		exec_status;

	exec_status = 0;

	io_files[0] = open(in_file, O_RDONLY);
	io_files[1] = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);

	append_exe_pkg(&x_lst, args);
	append_exe_pkg(&x_lst, args1);
	append_exe_pkg(&x_lst, args2);
	append_exe_pkg(&x_lst, args3);
	
	cur_rd = io_files[0];
	
	while (x_lst->next)
	{
		if (pipe(&(x_lst->rd)) < 0)
			return (lst_clear(&x_lst));
		printf("Pipe end : cur_rd %d, x_rd %d, x_wt %d\n", cur_rd, x_lst->rd, x_lst->wt);
		exec_status = spawn_proc_exec(&cur_rd, &x_lst->wt, x_lst->rd, x_lst->argv, env);
		print_pipe_content(&(x_lst->rd), 1);
//		print_pipe_content(x_lst->rd, x_lst->wt, 1);
		if (analyse_proc_exit(exec_status))
			return (lst_clear(&x_lst));
		cur_rd = x_lst->rd;
		lst_delone_xp(&x_lst, 0);
	}
	
	printf("Pipe to File : cur_rd %d, file %d\n", cur_rd, io_files[1]);
	exec_status = spawn_proc_exec(&cur_rd, &io_files[1], 0, x_lst->argv, env);
	if (analyse_proc_exit(exec_status))
		return (lst_clear(&x_lst));
	close(io_files[1]);
	return (0);
}
