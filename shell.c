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
	int len = 0, status = 0;
	char **av = NULL;
	int (*p_func)(char *exe, int ac, char **as, char **e, int st);

	(void)argc;
	(void)argv;
	signal(SIGINT, sigign);
	while (1)
	{
		print_prompt();
		nbchar = getline(&lineptr, &n, stdin);
		if (nbchar <= 0)
		{
			free(lineptr);
			exit(0);
		}
		av = parse_input(lineptr, e, status);
		len = array_len(av);
		if (len == 0)
		{
			free_args(av);
			continue;
		}
		p_func = get_buildin_func(av[0]);
		if (p_func != NULL)
		{
			status = p_func(argv[0], len, av, e, status);
			if (status != 0)
				execute_exit(status, av, lineptr);
		}
		else
			status = execmd(argv[0], av, e);
		free_args(av);

	}
	return (0);
}

