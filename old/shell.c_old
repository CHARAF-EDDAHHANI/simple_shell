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
	char **e = environ, **cmds;
	int status = 0, len = 0, i;

	(void)argc;
	signal(SIGINT, sigign);
	while (1)
	{
		print_prompt();
		nbchar = getline(&lineptr, &n, stdin);
		if (nbchar == -1)
		{
			free(lineptr);
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "\n", 1);
			if (status != 0)
				exit(status);
			return (0);
		}
		ignore_comments(lineptr);
		cmds = parse_multi_cmd(lineptr);
		for (i = 0; cmds[i] != NULL; i++)
		{
			argv = parse_input(argv[0], cmds[i]);
			if (replace_variables(argv, e, status) != 0)
				return (1);
			len = array_len(argv);
			if (len == 1)
				continue;
			status = execmd(len, argv, &e, status);
		}
		free(cmds);
	}
	free(lineptr);
	return (0);
}

