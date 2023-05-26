#include "shell.h"

/**
 * my_exit - exit the current process
 * @exe: executable name
 * @ac: number of arguments
 * @as: a pointer of pointers to arguments
 * @e: a pointer of environment variables
 * @s: the status of the previous command
 * @l: line number
 * Return: 0 success
 */


int my_exit(char *exe, int ac, char **as, char **e, int s, int l)
{
	int status = 200, i;
	char *error;
	char *level = convert_number(l, 10, 0);

	(void)e;
	if (ac > 2)
	{
		print_error(exe, "Usage: exit status");
		return (1);
	}
	if (as[1] != NULL)
	{
		for (i = 0; as[1][i] != '\0'; i++)
		{
			if (!_isdigit(as[1][i]))
			{
				error = malloc(sizeof(char) * (_strlen(as[1]) +
						       _strlen(level) + 27));
				_strcpy(error, level);
				_strcat(error, ": exit: ");
				_strcat(error, "Illegal number: ");
				_strcat(error, as[1]);
				print_error(exe, error);
				free(error);
				return (2);
			}
		}
		status = _atoi(as[1]);
	}
	else if (s != 0)
		status = s;
	return (status);
}


/**
 * my_env - print environment variables
 * @exe: executable name
 * @ac: number of arguments
 * @as: a pointer of pointers to arguments
 * @e: a pointer of environment variables
 * @s: the status of the previous command
 * @l: line number
 * Return: 0 success
 */

int my_env(char *exe, int ac, char **as, char **e, int s, int l)
{
	char **envp = e;

	(void)as;
	(void)s;
	(void)l;
	if (ac > 1)
	{
		print_error(exe, "Usage : env");
		return (1);
	}
	while (*envp)
	{
		write(STDOUT_FILENO, *envp, _strlen(*envp));
		write(STDOUT_FILENO, "\n", 1);
		envp++;
	}
	return (0);
}
