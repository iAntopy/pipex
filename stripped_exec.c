#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct s_exe_pkg
{
	s_exe_pkg	*next;
	char		**argv;
	int		rd;
	int		wt;
} t_exe_p;


int	exe_pkg_init(t_exe_p **x_lst, char **argv, int rd, int wt)
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
	xp->rd = rd;
	xp->wt = wt;
	if (*x_lst)
	{
		elem = *x_lst;
		while (elem->next)
			elem = elem->next;
		elem->next = xp;			*
	}
	else
		*x_lst = xp;
	return (0);
}

int	spawn_proc_exec(int rd, int wt, char **argv, char **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (1);
	}
	if (pid == 0)
	{
		dup2(wt, 1);
		dup2(rd, 0);
		if (execve(prog, argv, env) == -1)
			perror("Execution of program ls has failed");
		close(rd);
		close(wt);
		return (1);
	}
	printf("Parent process waiting ...\n");
	close(rd);
	close(wt);
	waitpid(pid, NULL, 0);
	printf("Parent process resumes.\n");
	if (errno)
		return (1);
	errno = 0;

	return (0);
}

int	main(int argc, char **argv[], char **env)
{
	char	prog[] = "/bin/ls";
	char	prog2[] = "/bin/grep";
	char	prog3[] = "/bin/cut;
	char	*args[3] = {prog, "-la", NULL};
	char	*args2[3] = {prog2, "main", NULL};
	char	*args3[4] = {prog3, "-d' '", "-f5", NULL};
	int	pid;
	int	pp[2];

	if (pipe(pp) < 0)
		return (1);
		
	spawn_proc_exec();	
	return (0);	

}
