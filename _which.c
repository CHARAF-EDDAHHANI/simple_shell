#include "shell.h"

/**
 * countPaths - returns the nbr of directories paths in PATH
 * @path: the value of PATH environement variable
 * Return: the nbr of directories paths
 */
int countPaths(char *path)
{
	int count = 0;
	char **tokens;

	tokens = _strtok(path, ":");
	while (*tokens)
	{
		count++;
		tokens++;
	}
	return (count);
}

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
	char **dirs = NULL;
	int i, nbrPaths = 0;
	char *path, *copyPath;
	struct stat st;

	if (stat(cmd, &st) == 0) /* check if the user enter a path */
		return (cmd);
	/* make a copy of path value */
	copyPath = _strdup(envPath);
	if (!copyPath)
		return (NULL);
	/* get the nbr of dir paths */
	nbrPaths = countPaths(copyPath);
	/* Allocate space to dir paths */
	dirs = malloc(sizeof(char *) * (nbrPaths + 1));
	if (!dirs)
		return (NULL);
	/* store the dir path in an array */
	dirs = _strtok(envPath, ":");
	if (dirs)
	{
		for (i = 0; dirs[i]; i++)
		{
			path = malloc(sizeof(char) * (_strlen(dirs[i]) +
							_strlen(cmd) + 2));
			if (!path)
				return (NULL);
			buildPath(dirs[i], cmd, path);
			if (stat(path, &st) == 0)
				return (path);
		}
	}
	return (NULL);
}
