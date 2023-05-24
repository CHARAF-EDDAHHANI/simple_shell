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
 * @lineptr: the line command
 * Return: a pointer of pointers to arguments
 */
char **parse_input(char *lineptr)
{
	char **av;
	char *token = NULL, *copy;
	int nbrTokens = 0, i = 0, j;
	const char *delim = " \t\n";

	copy = malloc(sizeof(char) * (_strlen(lineptr) + 1));
	if (copy == NULL)
		return (NULL);
	_strcpy(copy, lineptr);
	nbrTokens = count_token(copy, delim);
	av = malloc(sizeof(char *) * (nbrTokens + 1));
	if (!av)
		return (NULL);
	token = strtok(lineptr, delim);
	for (i = 0; token; i++)
	{
		av[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		if (av[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(av[j]);
			free(av);
			free(copy);
			return (NULL);
		}
		_strcpy(av[i], token);
		token = strtok(NULL, delim);
	}
	av[i] = NULL;
	free(copy);
	return (av);
}

