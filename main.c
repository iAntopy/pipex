/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:40:42 by iamongeo          #+#    #+#             */
/*   Updated: 2022/06/03 21:55:45 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>

const char program[] = "cat";
const char arg1[] = "-e";
const char EOP = '\0';

void	raw_print(char *str, size_t n, int fd)
{
	while (n--)
	{
		if (*str == '\0')
			write(fd, ".", 1);
		else
			write(fd, str++, 1);
	}
}

void	print_str_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		printf("%d - %s\n", i, tab[i]);
}

int	file_transfer(int from, int to)
{
	char	buff[1000];
	size_t	n_chrs;

	n_chrs = read(from, buff, 1000);
	while (n_chrs)
	{
		write(to, buff, n_chrs);
		if (buff[n_chrs - 1] == '\0')
		{
			printf("file transfer reached end with \\0.\n");
			break ;
		}
		n_chrs = read(from, buff, 1000);

	}
}

void	pipe_in_the_middle_print(int pp[2], int fd)
{
	char	buff[1000];
	size_t	n_chrs;

	printf("\n===== Content of pipe : =====\n");
	n_chrs = read(pp[0], buff, 1000);
	while (n_chrs)
	{
		write(fd, buff, n_chrs);
		write(pp[1], buff, n_chrs);
		if (buff[n_chrs - 1] == '\0')
			break ;
		n_chrs = read(pp[0], buff, 1000);
	}
	printf("\n=============================\n");
}

int	spawn_exec_proc(int pp[2], char **argv, char **env) 
{
	int	pid;
	int	wstatus;
	size_t	n_chrs;
	char	buff[100];

	pid = fork();
	if (pid == 0)
	{
		printf("read file : %d, write_file : %d\n", pp[0], pp[1]);
		print_str_tab(argv);
		printf("Child process (%d) begins exec\n", getpid());
		pipe_in_the_middle_print(pp, 1);
		dup2(1, 10);
		dup2(pp[0], 0);
		dup2(pp[1], 1);
		execve(argv[0], argv, env);
		pipe_in_the_middle_print(pp, 10);
		close(pp[0]);
		close(pp[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Process spawned, parent waiting ...\n");
		waitpid(pid, &wstatus, 0);
		printf("Child done, parent resumes, wstatus == %d\n", wstatus);
	}
	return (wstatus);
}

/*
int	main(int argc, char **argv, char **env)
{
	int	i;
	char	*prog1_args[2] = {argv[2], NULL};
	char	*prog2_args[3] = {argv[3], "jambon", NULL};
	int	pp[2];
	char	**pargs[2] = {prog1_args, prog2_args};
	int	io_files[2];

	printf("prog1 : %s, prog2 : %s\n", prog1_args[0], prog2_args[0]);
	if (pipe(pp) < 0)
		return (1);
	io_files[0] = open(argv[1], O_RDONLY);
	io_files[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	printf("in files : %s, out_file : %s\n", argv[1], argv[argc - 1]);
	if (io_files[0] < 0 || io_files[1] < 0)
		return (1);

	printf("io_files opened : %d, %d\n", io_files[0], io_files[1]);
	
	file_transfer(io_files[0], pp[1]);
	close(io_files[0]);
	close(pp[1]);
	printf("in_file transfer to pipe in DONE!\n");
	
	printf("spawning first process\n");
	spawn_exec_proc(pp, pargs[1], env);
	
//	pipe_in_the_middle_print(pp);
//	printf("spawning second process\n");
//	spawn_exec_proc(pp, pargs[1], env);
//	pipe_in_the_middle_print(pp);
	
	file_transfer(pp[0], io_files[1]);
	close(io_files[1]);
	close(pp[0]);
	printf("pipe out transfer to file_out DONE!\n");
	return (0);
}
*/
/*
int	main(int argc, char *argv[], char *env[])
{
	int		p[2];
	char	buff[100];
	int		pid;
	int		wstatus;

	if (pipe(p) < 0)
		return (1);
	
	write(p[1], "YOU CAN'T HANDLE THE TRUTH!\n", 28);
	pid = fork();

	close(p[1]);
	if (pid == 0)
	{
		printf("child pid : %d\n", getpid());
		dup2(0, p[0]);
		dup2(1, p[1]);
		char	*argv[3];
		argv[0] = program;
		argv[1] = arg1;
		argv[2] = NULL;
		execve(program, argv, env);
//		printf("woaw quess qui se passe\n");
		close(p[0]);
		close(p[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("parent pid : %d\n", getpid());
		close(p[1]);
		waitpid(pid, &wstatus, 0);
		read(p[0], buff, 100);
		raw_print(buff, 100, 1);
//		printf("returned from pipe : %s\n", buff);
	}
	return (0);
}
*/
