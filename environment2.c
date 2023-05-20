#include "shell.h"

/**
 * add_node_end - add a new element at the end of the list
 * @head: a pointer to a pointers to environement vars
 * @name: name of  the element
 * @value: value of the element
 * Return: pointer to the new element
 */

envNode_t *add_node_end(envNode_t **head, char *name, char *value)
{
	envNode_t *new;
	envNode_t *current = *head;

	while (current && current->next != NULL)
		current = current->next;
	new = malloc(sizeof(envNode_t));
	if (!new)
		return (NULL);
	new->name = _strdup(name);
	if (!new->name)
	{
		free_node(new);
		return (NULL);
	}
	if (value)
		new->value = _strdup(value);
	else
		new->value = _strdup("");
	if (!new->value)
	{
		free_node(new);
		return (NULL);
	}
	new->next = NULL;
	if (current)
		current->next = new;
	else
		*head = new;
	return (new);
}

/**
 * convert_to_list - converts the environ array to list
 * @envp: a pointer to an array of pointer to environment vars
 * Return: the first element of the list
 */

envNode_t *convert_to_list(char **envp)
{
	char *var, *name, *value;
	envNode_t *list = NULL;

	while (*envp)
	{
		var = _strdup(*envp);
		if (!var)
		{
			perror("Error - Not enough space");
			return (NULL);
		}
		name = strtok(var, "=");
		value = strtok(NULL, "\0");
		add_node_end(&list, name, value);
		envp++;
		free(var);
	}
	return (list);
}

/**
 * _setenv - add or change an environment variable
 * @head: a pointer of pointer to list of environment vars
 * @name: the name of the variable
 * @value: the value of the variable
 * @overwrite: 0 (the value will not be changed if the variable exists)
 * > 0 (the value will be changed if the variable exists)
 * Return: 0 (Success)
 */

int _setenv(envNode_t **head, char *name, char *value, int overwrite)
{
	envNode_t *current = *head;

	/* search for the node with matching name */
	while (current != NULL)
	{
		if (_strcmp(current->name, name) == 0)
		{
			if (overwrite)
			{
				free(current->value);
				if (value)
					current->value = _strdup(value);
				else
					current->value = _strdup("");
				if (!current->value)
				{
					perror("setenv - Not enough space");
					return (1);
				}
			}
			return (0);
		}
		current = current->next;
	}
	/*Node not found */
	if (add_node_end(head, name, value) == NULL)
	{
		perror("Error : setenv");
		return (1);
	}
	return (0);
}

/**
 * list_to_environ - converts a list to environ array
 * @head: a pointer to the first element of a list
 * Return: an array of pointer to environment variables
 */
char **list_to_environ(envNode_t *head)
{
	int i = 0, size = 0;
	char **new_environ;
	envNode_t *current = head;
	char *env_var;

	/* count the len of the list */
	size = list_len(head);
	/* Allocate space for the new environ */
	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
	{
		perror("Error - Not enough space");
		return (NULL);
	}
	/* stored the name-value pairs to the new environ array */
	while (current != NULL)
	{
		env_var = malloc((_strlen(current->name)
					+ _strlen(current->value) + 2)
				* sizeof(char));
		if (env_var == NULL)
		{
			perror("Error : Not enough space");
			return (NULL);
		}
		build_env_var(env_var, current->name, current->value);
		new_environ[i] = env_var;
		i++;
		current = current->next;
	}
	new_environ[i] = NULL;
	return (new_environ); /* Set the new environ array */
}

/**
 * _unsetenv - remove an environment variable
 * @head: a pointer to pointers of environment vars
 * @name: the name of the variable to be removed
 */
void _unsetenv(envNode_t **head, char *name)
{
	envNode_t *current = *head;
	envNode_t *previous = NULL;

	while (current != NULL)
	{
		if (_strcmp(current->name, name) == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free_node(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}
