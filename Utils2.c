#include "shell.h"

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

/**
 * replace_variables - handle variables
 * @args: an array of pointers to arguments
 * @e: an array of environment variables
 * @s: the previous status
 * Return: 0 Success
 */

int replace_variables(char **args, char **e, int s)
{
	int i;
	char *value;

	for (i = 0; args[i] != NULL; i++)
	{
		if (args[i][0] == '$' && args[i][1] == '\0')
			continue;
		else if (_strcmp(args[i], "$?") == 0)
		{
			free(args[i]);
			args[i] = _strdup(convert_number(s, 10, 0));
			continue;
		}
		else if (_strcmp(args[i], "$$") == 0)
		{
			free(args[i]);
			args[i] = _strdup(convert_number(getpid(), 10, 0));
			continue;
		}
		else if (args[i][0] == '$')
		{
			value = _getenv(&args[i][1], e);
			free(args[i]);
			if (value)
			{
				args[i] = _strdup(value);
				free(value);
				continue;
			}
			args[i] = _strdup("");
		}
	}
	return (0);
}
