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
	char *path, *token = NULL;
	struct stat st;

	if (stat(cmd, &st) == 0) /* check if the user enter a path */
		return (cmd);
	/* store the dir path in an array */
	token = strtok(envPath, ":");
	while (token)
	{
		path = malloc(sizeof(char) * (_strlen(token) +
					_strlen(cmd) + 2));
		if (!path)
		{
			free(token);
			return (NULL);
		}
		buildPath(token, cmd, path);
		if (stat(path, &st) == 0)
			return (path);
		token = strtok(NULL, ":");
	}
	free(token);
	return (NULL);
}
