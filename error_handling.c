#include "pipex.h"

int	perror_ENOENT()
{
	errno = ENOENT;
	perror("pipex file error");
	return (-1);
}

int	perror_EACCES()
{
	errno = EACCES;
	perror("pipex file error");
	return (-1);
}

