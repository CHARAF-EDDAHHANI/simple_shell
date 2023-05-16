#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: the envirment variable name
 * Return: the environment variable
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
