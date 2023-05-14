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
	(void)argv;
	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		nbchar = getline(&lineptr, &n, stdin);
		if (nbchar == -1)
		{	
			free(lineptr);
			write(STDOUT_FILENO, "\n", 1);
			return (0);
		}
		argv[1] = malloc(sizeof(char) * _strlen(lineptr));
		if (!argv[1])
		{
			perror(argv[0]);
		}
		_strncat(argv[1], lineptr, _strlen(lineptr) - 1);
		execmd(argv);
	}	
	free(lineptr);
	return (0);
}

