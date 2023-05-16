#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: the environment variable name
 * Return: the environment variable value
 */
char *_getenv(const char *name)
{
	char **variable;
	char **envp = environ;

	while (envp)
	{
		variable = _strtok(*envp, "=");
		if (variable)
		{
			if (_strcmp(*variable, name) == 0)
				return (*(variable + 1));
		}
		free(variable);
		envp++;
	}
	free(envp);
	return (NULL);
}


/**
 * _getenv2 - gets an environment variable
 * @name: the environment variable name
 * Return: the environment variable value
 */

char *_getenv2(const char *name)
{
	char *token;
	char **envp = environ;

	while (envp)
	{
		token = strtok(*envp, "=");
		if (token)
		{
			if (_strcmp(token, name) == 0)
				return (strtok(NULL, "="));
		}
		envp++;
	}
	return (NULL);
}

/**
 * printDirPaths - prints dir Paths contains in PATH variable
 * @path: the value of PATH environment variable
 */
void printDirPaths(char *path)
{
	char **dirPaths;

	dirPaths = _strtok(path, ":");
	if (dirPaths)
	{
		while (*dirPaths)
		{
			/*printf("%s\n", *dirPaths);*/
			write(STDOUT_FILENO, *dirPaths, _strlen(*dirPaths));
			write(STDOUT_FILENO, "\n", 1);
			dirPaths++;
		}
	}
}
