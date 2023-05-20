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
 * @e: an array of environment variables
 * Return: the environment variable value
 */

char *_getenv2(const char *name, char **e)
{
	char *token;
	char **envp = e;
	char *variable;

	while (envp)
	{
		variable = _strdup(*envp);
		if (!variable)
			return (NULL);
		token = strtok(variable, "=");
		if (token)
		{
			if (_strcmp(token, name) == 0)
				return (strtok(NULL, "\0"));
		}
		envp++;
		free(variable);
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
			write(STDOUT_FILENO, *dirPaths, _strlen(*dirPaths));
			write(STDOUT_FILENO, "\n", 1);
			dirPaths++;
		}
	}
}


/**
 * list_len - returns the length od a list
 * @list: the giving list
 * Return: the length of the list
 */

int list_len(envNode_t *list)
{
	int len = 0;

	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

/**
 * print_env_list - prints an environment variables list
 * @envp: a pointer of the first element of the list
 */

void print_env_list(const envNode_t *envp)
{
	while (envp)
	{
		if (envp->name)
			write(STDOUT_FILENO, envp->name, _strlen(envp->name));
		write(STDOUT_FILENO, "=", 1);
		if (envp->value)
			write(STDOUT_FILENO, envp->value, _strlen(envp->value));
		write(STDOUT_FILENO, "\n", 1);
		envp = envp->next;
	}
}
