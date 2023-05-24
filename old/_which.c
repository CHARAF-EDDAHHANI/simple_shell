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

	if (stat(cmd, &st) == 0) /* check if the user enter a path */
		return (cmd);
	copyPath = _strdup(envPath);
	if (!copyPath)
		return (NULL);
	/* store the dir path in an array */
	token = strtok(copyPath, ":");
	while (token)
	{
		path = malloc(sizeof(char) * (_strlen(token) +
					_strlen(cmd) + 2));
		if (!path)
		{
			perror("malloc");
			free(token);
			return (NULL);
		}
		buildPath(token, cmd, path);
		if (stat(path, &st) == 0)
			return (path);
		token = strtok(NULL, ":");
	}
	free(copyPath);
	free(token);
	return (NULL);
}
