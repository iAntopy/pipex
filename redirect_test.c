#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static const char OUT_FILE[] = "qwers";
static const char IN_FILE[] = "asdf";

int	spawn_proc_exec(int pp[2], char **argv, char **env)
{
	int	pid;
	int	wstatus;

	pid = fork();
	if (pid == 0)
	{
		dup2(pp[0], 0);
		dup2(pp[1], 1);
		close(pp[0]);
		close(pp[1]);
		execve("grep", argv, env);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(pp[0]);
		close(pp[1]);
		waitpid(pid, &wstatus, 0);
	}
	else
		return (-1);
	return (wstatus);
}

int	main(int argc, char **argv, char **env)
{
	char	buff[] = "Je suis un jambon";
	char	*grep_args[3] = {"ls" "-la", NULL};
	int	pp[2];
	int	in;
	int	out;
	int	pid;
	int	proc_status;

	in = open(IN_FILE, O_RDONLY);
	out = open(OUT_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (in < 0 || out < 0)
		return (1);

	pid = fork();
	if (pid == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		execve("ls", grep_args, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}

//	pp[0] = in;
//	pp[1] = out;

//	proc_status = spawn_proc_exec(pp, grep_args, env);
//	printf("proc status : %d\n", proc_status);
//	dup2(1, 10);
//	write(10, buff, 18);
//	dup2(out, 1);
	close(out);
	close(in);
	return (0);
}
