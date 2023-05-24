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
	char **e = environ;
	int len = 0;
	char **av = NULL;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigign);
	while (1)
	{
		print_prompt();
		nbchar = getline(&lineptr, &n, stdin);
		if (nbchar == -1)
		{
			free(lineptr);
			return (0);
		}
		av = parse_input(lineptr);
		len = array_len(av);
		if (len == 0)
		{
			free_args(av);
			continue;
		}
		execmd(argv[0], av, e);
		free_args(av);
	}
	return (0);
}

