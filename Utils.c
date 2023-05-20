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
 * print_error - print an error message
 * @argv: an array of pointer to arguments
 * @desc: the error description
 * @r: the value to be returned
 * Return: return the value of the third argument
 */
int print_error(char **argv, char *desc, int r)
{
	char *error;

	error = build_error(argv[0], argv[1], desc);
	write(STDERR_FILENO, error, _strlen(error));
	return (r);
}
