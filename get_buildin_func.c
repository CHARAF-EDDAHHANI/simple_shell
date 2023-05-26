#include "shell.h"


/**
 * get_func - get build in function
 * @c: the giving command
 * Return: the associated function
 */

int (*get_func(char *c))(char *x, int n, char **a, char **e, int s, int l)
{
	buildin_t b_in[] = {
		{"exit", my_exit},
		{"env", my_env},
		{NULL, NULL}
	};
	int i;

	i = 0;

	while (i < 2)
	{
		if (!_strcmp(b_in[i].cmd, c))
			return (b_in[i].func);
		i++;
	}
	return (NULL);
}
