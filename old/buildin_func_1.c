#include "shell.h"


/**
 * replace_variables - handle variables
 * @args: an array of pointers to arguments
 * @e: an array of environment variables
 * @s: the previous status
 * Return: 0 Success
 */
int replace_variables(char **args, char **e, int s)
{
	envNode_t *list;
	int i;
	char *value;

	list = convert_to_list(e);
	for (i = 0; args[i] != NULL; i++)
	{
		if (args[i][0] == '$' && args[i][1] == '\0')
			continue;
		else if (_strcmp(args[i], "$?") == 0)
		{
			args[i] = _strdup(convert_number(s, 10, 0));
			if (!args[i])
				return (print_error(args, "Not enough space", 1));
			continue;
		}
		else if (_strcmp(args[i], "$$") == 0)
		{
			args[i] = _strdup(convert_number(getpid(), 10, 0));
			if (!args[i])
				return (print_error(args, "Not enough space", 1));
			continue;
		}
		else if (args[i][0] == '$')
		{
			value = get_node_by_name(list, &args[i][1]);
			if (value)
			{
				args[i] = _strdup(value);
				if (!args[i])
					return (print_error(args, "Not enough space", 1));
				continue;
			}
			args[i] = _strdup("");
			if (!args[i])
				return (print_error(args, "Not enough space", 1));
		}
	}
	return (0);
}


