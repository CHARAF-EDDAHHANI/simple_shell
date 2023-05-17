#include "shell.h"

/**
 * my_exit - exit the current process
 * Return: 0 success
 */
int my_exit(void)
{
	exit(0);
}

/**
 * my_env - print environment variables
 * Return: 0 success
 */

int my_env(void)
{
	char **envp = environ;

	while (*envp)
	{
		write(STDOUT_FILENO, *envp, _strlen(*envp));
		write(STDOUT_FILENO, "\n", 1);
		envp++;
	}
	return (0);
}
