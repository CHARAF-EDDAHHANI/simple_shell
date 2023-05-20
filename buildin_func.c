#include "shell.h"

/**
 * my_exit - exit the current process
 * @argc: number of arguments
 * @args: a pointer of pointers to arguments
 * @e: a pointer of environment variables
 * Return: 0 success
 */
int my_exit(int argc, char **args, char ***e)
{
	(void)argc;
	(void)args;
	(void)e;
	exit(0);
}

/**
 * my_env - print environment variables
 * @argc: number of arguments
 * @args: a pointer of pointers to arguments
 * @e: a pointer of environment variables
 * Return: 0 success
 */

int my_env(int argc, char **args, char ***e)
{
	char **envp = *e;

	(void)argc;
	(void)args;
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
 * Return: 0 success
 */
int set_env(int argc, char **args, char ***e)
{
	envNode_t *env;
	int ret;
	char *error;

	if (argc != 4)
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
 * Return: 0 Success
 */
int unset_env(int argc, char **args, char ***e)
{
	envNode_t *env;
	char *error;

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
 * Return: 0 Success
 */
int my_cd(int argc, char **args, char ***e)
{
	char *new_dir, *old, *error;
	int retVal = 0;
	envNode_t *h;
	char buf[1024];

	if (argc > 3)
	{
		error = build_error(args[0], "unsetenv", "Usage : cd [DIRECTORY]");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	h = convert_to_list(*e);
	if (args[2] == NULL) /* should be interpreted as cd $HOME */
		new_dir = _getenv2("HOME", *e);
	else if (_strcmp(args[2], "-") == 0)
		new_dir = get_node_by_name(h, "OLDPWD");
	else
		new_dir = args[2];
	old = _strdup(get_node_by_name(h, "PWD"));
	retVal = chdir(new_dir);
	if (retVal == -1)
	{
		error = build_error(args[0], "cd", "Error - chgt the working directory");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	if (old == NULL || (getcwd(buf, 1024)) == NULL)
	{
		error = build_error(args[0], "cd", "Error - getting the current directory");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	if (_setenv(&h, "PWD", getcwd(buf, 1024), 1) || _setenv(&h, "OLDPWD", old, 1))
	{
		error = build_error(args[0], "cd", "Error - setting PWD & OLDPWD");
		write(STDERR_FILENO, error, _strlen(error));
		return (1);
	}
	*e = list_to_environ(h);
	return (0);
}

