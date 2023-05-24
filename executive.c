#include "shell.h"

/**
 * sigign - prints a new line when a signal SIGINT is sent
 * @signal: the sent signal
 */

void sigign(int signal)
{
	if (signal == SIGINT)
		write(STDIN_FILENO, "\n$ ", 3);
}

/**
 * execmd - executes the giving command
 * @exe: executable name
 * @av: an array of arguments
 * @e: an array of environement variables
 * Return: status code
 */

int execmd(char *exe, char **av, char **e)
{
	pid_t child;
	int st;

	if (av)
	{
		child = fork();
		if (child == -1)
		{
			print_error(exe, "Fork fails");
			return (1);
		}
		else if (child == 0)
		{
			if (execve(av[0], av, e) == -1)
			{
				perror(exe);
				exit(errno);
			}
		}
		wait(&st);
		return (WEXITSTATUS(st));
	}
	return (0);
}

/**
 * print_error - print error message
 * @exe: executable name
 * @desc: error message
 */
void print_error(char *exe, char *desc)
{
	char *error;

	error = malloc(sizeof(char) * (_strlen(exe) + _strlen(desc) + 3));
	if (error == NULL)
	{
		write(STDERR_FILENO, "Not enough space", 16);
		return;
	}
	_strcpy(error, exe);
	_strcat(error, ": ");
	_strcat(error, desc);
	write(STDERR_FILENO, error, _strlen(error));
	free(error);
}
