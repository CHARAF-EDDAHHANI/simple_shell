#include "shell.h"


/**
 * execmd - executes the giving command
 * @argv: an array of arguments
 * Return: status code
 */

int execmd(char **argv)
{
	char *envPath, *cmd;

	/* get environment PATH value */
	envPath = _getenv("PATH");
	if (argv)
	{
		cmd = _which(argv[1], envPath);
		if (!cmd)
		{
			cmd = _strdup(argv[1]);
			if (!cmd)
				perror(argv[0]);
		}
		if (execve(cmd, argv + 1, environ) == -1)
		{
			perror(argv[0]);
			return (errno);
		}
	}
	return (0);
}

/**
 * build_error - build the error message
 * @exe: the executable name
 * @cmd: the giving command
 * @errorDesc: the error description
 * Return: The error message
 */
char *build_error(char *exe, char *cmd, char *errorDesc)
{
	char *error;

	error = malloc(sizeof(char) * (_strlen(exe)
				+ _strlen(errorDesc)
				+ _strlen(cmd)
				+ 6));
	if (!error)
		return (NULL);
	_strcpy(error, exe);
	_strcat(error, ": ");
	_strcat(error, cmd);
	_strcat(error, ": ");
	_strcat(error, errorDesc);
	_strcat(error, "\n\0");
	return (error);
}

/**
 * siging - prints a new line when a signal SIGINT is sent
 * @signal: the sent signal
 */

void sigign(int signal)
{
	if (signal == SIGINT)
		write(STDIN_FILENO, "\n$ ", 3);
}
