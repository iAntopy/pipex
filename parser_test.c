#include "pipex.h"

int	main(int argc,  char **argv,  char **env)
{
	char	**env_paths;
//	char	path[] = "/usr/bin";
//	char	path2[] = "/bin";
	char	file[] = "asdf";
	char	*parsed_path;

	env_paths = get_paths_table(env);

	if (!search_file_in_env(file, env_paths, &parsed_path))
		return (perror_ENOENT());
	else if (access(parsed_path, W_OK) != 0)
		return (perror_EACCES());
	printf("file : %s : ACCESS GRANTED\n", parsed_path);
//	parsed_path = parse_full_path(path2, file);
/*
	if (!parsed_path)
		return (1);
	printf("parsed path : %s\n", parsed_path);
	if (access(parsed_path, F_OK) != 0)
	{
		errno = ENOENT;
		perror("pipex file error");
	}
	else if (access(parsed_path, X_OK) != 0)
	{
		errno = EACCES;
		perror("pipex file error");
	}
	else
		printf("ACCESS GRANTED\n");
*/

	/*
	if (access("///////////bin////////////ls/", X_OK) == 0)
		printf("ACCESS GRANTED\n");
	else
		printf("ACCESS DENIED\n");
	*/
	free(env_paths);
	free(parsed_path);

	return (0);
}
