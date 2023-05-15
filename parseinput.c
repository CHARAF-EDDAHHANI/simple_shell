#include "shell.h"

/**
 * count_token - returns the number of tokens in the line command
 * @lineptr: the line command
 * @delim: a string of delimiters
 * Return: the nbr of tokens
 */

int count_token(char *lineptr, const char *delim)
{
	int nbtokens = 0;
	char *token;

	token = strtok(lineptr, delim);
	while (token)
	{
		nbtokens++;
		token = strtok(NULL, delim);
	}
	return (nbtokens);
}

/**
 * parse_input - splits line command into arguments
 * @execName: the name of shell executable
 * @lineptr: the line command
 * Return: a pointer of pointers to arguments
 */
char **parse_input(char *execName, char *lineptr)
{
	char **av;
	char *cplineptr, *token = NULL;
	int nbrTokens = 0, i = 0;
	const char *delim = " \n";

	cplineptr = _strdup(lineptr);
	if (!cplineptr)
		return (NULL);
	nbrTokens = count_token(cplineptr, delim);
	av = malloc(sizeof(char *) * (nbrTokens + 2));
	if (!av)
	{
		free(cplineptr);
		return (NULL);
	}
	av[0] = _strdup(execName);
	if (!av[0])
	{
		free(cplineptr);
		free(av);
		return (NULL);
	}
	token = strtok(lineptr, delim);
	for (i = 1; token; i++)
	{
		av[i] = _strdup(token);
		if (!av[i])
		{
			while (--i)
				free(av[i]);
			free(av);
			free(cplineptr);
			return (NULL);
		}
		token = strtok(NULL, delim);
	}
	av[i] = NULL;
	free(cplineptr);
	return (av);
}
