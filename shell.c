#include "shell.h"

/**
 * main - entry points to the simple version of the shell
 * @argc: nbr of arguments
 * @argv: an array of pointers of arguments
 * Return:0 success
 */


int main(int argc, char **argv)
{
	ssize_t nbchar = 0;
	size_t n = 0;
	char *lineptr = NULL;

	(void)argc;
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "$ ", 2);
		nbchar = getline(&lineptr, &n, stdin);
		if (nbchar == -1)
		{
			free(lineptr);
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		if (_strcmp(lineptr, "\n") == 0)
			continue;
		argv = parse_input(argv[0], lineptr);
		execmd(argv);
	}
	free(lineptr);
	return (0);
}

