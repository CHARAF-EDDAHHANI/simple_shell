#include "shell.h"

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
char ** parse_input(char *lineptr)
{
	char **av;
	char *cplineptr;

	cplineptr = _strdup(lineptr);
	if (!cplineptr)
		return (NULL);
