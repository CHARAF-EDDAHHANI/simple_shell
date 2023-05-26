#include "shell.h"

/**
 * _strlen - returns the length of string
 * @str: the giving string
 * Return: the length of the string
 */

int _strlen(char *str)
{
	int len = 0, i = 0;

	while (str[i++])
		len++;
	return (len);
}

/**
 * isDelim - check if a character is delimiter
 * @c: the giving character
 * @delim: a string of delimiter characters
 * Return: 1 (if c is delimiter), 0 otherwize
 */
int isDelim(char c, const char *delim)
{
	int i = 0;

	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}


/**
 * tokenCount - counts the number of token in a string
 * @str: the giving string
 * @delim: a string of delimiters
 * Return: the number of tokens
 */
int tokenCount(char *str, const char *delim)
{
	int count = 0, i, isNewWord = 1;

	for (i = 0; str[i]; i++)
	{
		if (isDelim(str[i], delim))
			isNewWord = 1;
		else if (isNewWord == 1)
		{
			count++;
			isNewWord = 0;
		}
	}
	return (count);
}

/**
 * _strtok - splits a string into tokens
 * @str: the giving string
 * @delim: a string of delimiters
 * Return: an array of pointers to tokens
 */
char **_strtok(char *str, const char *delim)
{
	int nbrTokens = 0, len = 0, i, tLen = 0, k = 0, tStart = 0, tEnd = 0, j, l;
	char **tokens;

	if (str == NULL)
		return (NULL);
	nbrTokens = tokenCount(str, delim);
	if (nbrTokens == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (nbrTokens + 1));
	if (!tokens)
	{
		perror("Error : malloc");
		return (NULL);
	}
	len = _strlen(str);
	for (i = 0; i <= len; i++)
	{
		if (str[i] && !isDelim(str[i], delim) && tLen++ == 0)
			tStart = i;
		else if (isDelim(str[i], delim) || !str[i])
		{
			if (tLen)
			{
				tEnd = i - 1;
				tokens[k] = malloc((tLen + 1) * sizeof(char));
				if (!tokens[k])
				{
					perror("Error : malloc");
					while (k >= 0)
						free_list(tokens, k);
				}
				for (j = tStart, l = 0; j <= tEnd; j++, l++)
					tokens[k][l] = str[j];
				tokens[k][l] = '\0';
				tLen = 0, k++;
			}
		}
	}
	tokens[k] = NULL;
	return (tokens);
}

/**
 * _strdup - returns a pointer to duplicated string
 * @str: the giving string
 * Return: a pointer to the duplicated string or NULL if it fails
 */
char *_strdup(char *str)
{
	char *dupString;
	int length = 0, i;

	if (!str)
		return (NULL);
	length = _strlen(str);
	/* Allocate space for the duplicate string */
	dupString = malloc(sizeof(char) * (length + 1));
	/* Check if the allocation it fails or not */
	if (!dupString)
	{
		perror("Error : malloc");
		return (NULL);
	}
	/* copy the string */
	for (i = 0; i < length; i++)
		dupString[i] = str[i];
	/* Add the end of string character */
	dupString[i] = '\0';
	return (dupString);
}
