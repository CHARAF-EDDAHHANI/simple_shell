#include "shell.h"

/**
 * get_buildin_func - get build in function
 * @c: the giving command
 * Return: the associated function
 */

int (*get_buildin_func(char *c))(int argc, char **args, char ***e)
{
	buildin_t b_in[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"cd", my_cd},
		{NULL, NULL}
	};
	int i;

	i = 0;

	while (i < 5)
	{
		if (!_strcmp(b_in[i].cmd, c))
			return (b_in[i].func);
		i++;
	}
	return (NULL);
}
