#include "shell.h"


/**
 * execmd - executes the giving command
 * @argv: an array of arguments
 */

void execmd(char **argv)
{
	if (argv)
	{
		if (execve(argv[1], argv + 1, environ) == -1)
		{
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			perror("");
			exit(EXIT_FAILURE);
		}
	}
}

