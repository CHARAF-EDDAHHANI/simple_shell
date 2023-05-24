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
	free(error);
	return (r);
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

/**
 * convert_number - converts an integer to a specific base
 * @n: the giving integer
 * @base: the base to be converted to
 * @upper_o_n: indicates if output upper od lower case
 * Return: the conversion string
 */

char *convert_number(int n, int base, int upper_o_n)
{
	static char *base_digits;
	static char buffer[50];
	char *p_convert;

	base_digits = upper_o_n ? "0123456789ABCDEF" :
				"0123456789abcdef";

	p_convert = &buffer[49];
	*p_convert = '\0';

	do {
		*--p_convert = base_digits[n % base];
		n /= base;
	} while (n != 0);
	return (p_convert);
}
