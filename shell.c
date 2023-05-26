#include "shell.h"

/**
 * main - entry points to the simple version of the shell
 * @argc: nbr of arguments
 * @argv: an array of pointers of arguments
 * Return:0 success
 */


int main(__attribute__((unused)) int argc, char **argv)
{
	ssize_t nbchar = 0;
	size_t n = 0;
	char *lineptr = NULL;
	char **e = environ, **av = NULL, **cmd = NULL;
	int len = 0, status = 0, i;
	int (*p_func)(char *exe, int ac, char **as, char **e, int st);

	signal(SIGINT, sigign);
	while (1)
	{
		print_prompt();
		nbchar = getline(&lineptr, &n, stdin);
		if (nbchar <= 0)
		{
			free(lineptr);
			exit(status);
		}
		cmd = parse_multi_cmd(lineptr);
		for (i = 0; cmd[i]; i++)
		{
			av = parse_input(cmd[i], e, status);
			len = array_len(av);
			if (len > 0)
			{
				p_func = get_buildin_func(av[0]);
				if (p_func != NULL)
				{
					status = p_func(argv[0], len, av, e, status);
					if (status != 0)
						execute_exit(status, av, lineptr, cmd);
				}
				else
					status = execmd(argv[0], av, e);
			}
			free_args(av);
		}
		free_args(cmd);
	}
	return (0);
}

