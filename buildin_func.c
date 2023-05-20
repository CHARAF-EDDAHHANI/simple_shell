#include "shell.h"

/**
 * my_exit - exit the current process
 * @argc: number of arguments
 * @args: a pointer of pointers to arguments
 * @e: a pointer of environment variables
 * @s: the status of the previous command
 * Return: 0 success
 */
int my_exit(int argc, char **args, char ***e, int s)
{
	int status = 0, i;
	char *error;

	(void)e;
	if (argc > 3)
	{
		error = build_error2(args[0], "Usage: exit status");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	if (args[2] != NULL)
	{
		for (i = 0; args[2][i] != '\0'; i++)
		{
			if (i == 0 && args[2][i] == '-')
				continue;
			if (!_isdigit(args[2][i]))
			{
				error = build_error2(args[0], "exit : numeric argument required");
				write(STDERR_FILENO, error, _strlen(error));
				return (2);
			}
		}
		status = _atoi(args[2]);
	}
	else
		status = s;
	exit(status);
}

/**
 * my_env - print environment variables
 * @argc: number of arguments
 * @args: a pointer of pointers to arguments
 * @e: a pointer of environment variables
 * @s: the status of the previous command
 * Return: 0 success
 */

int my_env(int argc, char **args, char ***e, int s)
{
	char **envp = *e;
	char *error;

	(void)args;
	(void)s;
	if (argc > 2)
	{
		error = build_error2(args[0], "Usage : env");
		write(STDERR_FILENO, error, _strlen(error));
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	while (*envp)
	{
		write(STDOUT_FILENO, *envp, _strlen(*envp));
		write(STDOUT_FILENO, "\n", 1);
		envp++;
	}
	return (0);
}

/**
 * set_env - Initialize a new environment variable, or modify an existing one
 * @argc: number of arguments
 * @args: a pointer of pointers to arguments
 * @e: a pointer of pointers to environment variables
 * @s: the status of the previous command
 * Return: 0 success
 */
int set_env(int argc, char **args, char ***e, int s)
{
	envNode_t *env;
	int ret;
	char *error;

	(void)s;
	if (argc > 4)
	{
		error = build_error(args[0], "setenv", "Usage : setenv VARIABLE VALUE");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	env = convert_to_list(*e);
	ret = _setenv(&env, args[2], args[3], 1);
	if (ret != 0)
	{
		error = build_error(args[0], "Error", "setenv");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	*e = list_to_environ(env);
	return (0);
}

/**
 * unset_env - Remove an environment variable
 * @argc: number of arguments
 * @args: an array of pointer to arguments
 * @e: a pointer to environment variables
 * @s: the status of the previous command
 * Return: 0 Success
 */
int unset_env(int argc, char **args, char ***e, int s)
{
	envNode_t *env;
	char *error;

	(void)s;
	if (argc != 3)
	{
		error = build_error(args[0], "unsetenv", "Usage : unsetenv VARIABLE");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	env = convert_to_list(*e);
	_unsetenv(&env, args[2]);
	*e = list_to_environ(env);
	return (0);
}

/**
 * my_cd - change the working directory
 * @argc: number of arguments
 * @args: an array of pointer to arguments
 * @e: a pointer to environment variables
 * @s: the status of the previous command
 * Return: 0 Success
 */
int my_cd(int argc, char **args, char ***e, __attribute__((unused)) int s)
{
	char *new_dir, *old, *error, buf[1024];
	int retVal = 0;
	envNode_t *h;

	if (argc > 3)
		return (print_error(args, "Usage : cd [DIRECTORY]", 1));
	h = convert_to_list(*e);
	if (args[2] == NULL) /* should be interpreted as cd $HOME */
	{
		new_dir = get_node_by_name(h, "HOME");
		if (!new_dir)
			return (print_error(args, "HOME not set", 1));
	}
	else if (_strcmp(args[2], "-") == 0)
	{
		new_dir = get_node_by_name(h, "OLDPWD");
		if (!new_dir)
			return (print_error(args, "OLDPWD not set", 1));
	}
	else
		new_dir = args[2];
	old = _strdup(get_node_by_name(h, "PWD"));
	retVal = chdir(new_dir);
	if (retVal == -1 && errno == EACCES)
	{
		error = malloc(sizeof(char) * (_strlen(new_dir) + 13));
		if (!error)
			return (print_error(args, "Not enough space", 1));
		_strcpy(error, "can't cd to ");
		_strcat(error, new_dir);
		return (print_error(args, error, 2));
	}
	else if (retVal == -1 && errno != EACCES)
		return (print_error(args, "Error - chgt the working directory", 1));
	if (old == NULL || (getcwd(buf, 1024)) == NULL)
		return (print_error(args, "Error - getting the current directory", 1));
	if (_setenv(&h, "PWD", getcwd(buf, 1024), 1) || _setenv(&h, "OLDPWD", old, 1))
		return (print_error(args, "Error - setting PWD & OLDPWD", 1));
	*e = list_to_environ(h);
	return (0);
}

