#include "shell.h"

/**
 * buildPath - build the command path
 * @dirPath: the giving directory path
 * @cmd: the giving command
 * @path: the command path
 */

void buildPath(char *dirPath, char *cmd, char *path)
{
	_strcpy(path, dirPath);
	_strcat(path, "/");
	_strcat(path, cmd);
	_strcat(path, "\0");
}


/**
 * _which - locate a command
 * @cmd: the giving command
 * @envPath: the value of PATH environnement variable
 * Return: the path of the command or NULL if that not exists
 */

char *_which(char *cmd, char *envPath)
{
	char *path, *token = NULL, *copyPath;
	struct stat st;

	if (stat(cmd, &st) == 0)
	{
		path = malloc(sizeof(char) * (_strlen(cmd) + 1));
		_strcpy(path, cmd);
		return (path);
	}
	copyPath = malloc(sizeof(char) * (_strlen(envPath) + 1));
	if (!copyPath)
		return (NULL);
	_strcpy(copyPath, envPath);
	/* store the dir path in an array */
	token = strtok(copyPath, ":");
	while (token)
	{
		path = malloc(sizeof(char) * (_strlen(token) +
					_strlen(cmd) + 2));
		if (!path)
		{
			perror("malloc");
			free(copyPath);
			return (NULL);
		}
		buildPath(token, cmd, path);
		if (stat(path, &st) == 0)
		{
			free(copyPath);
			return (path);
		}
		token = strtok(NULL, ":");
		free(path);
	}
	free(copyPath);
	return (NULL);
}
