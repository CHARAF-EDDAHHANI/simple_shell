#include "shell.h"

/**
 * print_prompt - prints the prompt string
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * free_args - free an array of string
 * @av: an array of strings
 */

void free_args(char **av)
{
	int i = 0;

	while (av[i] != NULL)
	{
		free(av[i]);
		i++;
	}
	free(av);
}

/**
 * _getenv - gets an environment variable
 * @name: the environment variable name
 * @e: an array of environment variables
 * Return: the environment variable value
 */

char *_getenv(const char *name, char **e)
{
	char *variable, *token, *path;
	char **envp = e;

	while (*envp)
	{
		variable = malloc(sizeof(char) * (_strlen(*envp) + 1));
		if (variable == NULL)
			return (NULL);
		_strcpy(variable, *envp);
		token = strtok(variable, "=");
		if (token != NULL && _strcmp(token, name) == 0)
		{
			token = strtok(NULL, "\0");
			if (token != NULL)
			{
				path = malloc(sizeof(char) * (_strlen(token) + 1));
				if (path == NULL)
					return (NULL);
				_strcpy(path, token);
				free(variable);
				return (path);
			}
			free(variable);
			return (NULL);
		}
		envp++;
		free(variable);
	}
	return (NULL);
}

/**
 * execute_exit - launch exit command
 * @status: the exit status
 * @av: an array of arguments
 * @cmd: an array of commands
 * @line: the line
 */

void execute_exit(int status, char **av, char *line, char **cmd)
{
	free_args(av);
	free(line);
	free_args(cmd);
	if (status == 200)
		exit(0);
	exit(status);
}


/**
 * ignore_comments - ignore the comments
 * @lineptr : the giving string
 */

void ignore_comments(char *lineptr)
{
	int i;

	for (i = 0; lineptr[i] != '\0'; i++)
	{
		if (lineptr[i] == '#' && (i == 0 || lineptr[i - 1] == ' '))
		{
			lineptr[i] = '\0';
			return;
		}
	}
}
