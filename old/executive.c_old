#include "shell.h"


/**
 * execmd - executes the giving command
 * @argc: number of arguments
 * @argv: an array of arguments
 * @e: an array of environement variables
 * @s: the status of the previous command
 * Return: status code
 */

int execmd(int argc, char **argv, char ***e, int s)
{
	char *envPath, *cmd;
	pid_t pid;
	int st;
	int (*p_func)(int argc, char **args, char ***e, int st);

	envPath = _getenv2("PATH", *e);/* get environment PATH value */
	if (argv)
	{
		p_func = get_buildin_func(argv[1]);
		if (p_func != NULL)
			return (p_func(argc, argv, e, s));
		cmd = _which(argv[1], envPath);
		if (cmd != NULL)
		{
			pid = fork();
			if (pid == -1)
			{
				perror(build_error2(argv[0], "fork"));
				return (1);
			}
			if (pid == 0)
			{
				if (execve(cmd, argv + 1, *e) == -1)
				{
					free(cmd);
					perror(build_error2(argv[0], "execve"));
					exit(errno);
				}
			}
			wait(&st);
			free(cmd);
			return (WEXITSTATUS(st));
		}
		else
			return (print_cmd_not_found(argv));
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
	{
		perror("Error : malloc");
		return (NULL);
	}
	_strcpy(error, exe);
	_strcat(error, ": ");
	_strcat(error, cmd);
	_strcat(error, ": ");
	_strcat(error, errorDesc);
	_strcat(error, "\n\0");
	return (error);
}

/**
 * build_error2 - build a header of the error message
 * @exe: the executable name
 * @cmd: the command name
 * Return: the error header
 */

char *build_error2(char *exe, char *cmd)
{
	char *error;

	error = malloc(sizeof(char) * (_strlen(exe)
				+ _strlen(cmd)
				+ 3));
	if (!error)
	{
		perror("Error : malloc");
		return (NULL);
	}
	_strcpy(error, exe);
	_strcat(error, ": ");
	_strcat(error, cmd);
	_strcat(error, "\0");
	return (error);
}

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
 * print_cmd_not_found - prints command not found error
 * @argv: an array of pointers to arguments
 * Return: 127
 */
int print_cmd_not_found(char **argv)
{
	char *error;

	error = build_error(argv[0], argv[1], "command not found");
	write(STDERR_FILENO, error, _strlen(error));
	free(error);
	return (127);
}
