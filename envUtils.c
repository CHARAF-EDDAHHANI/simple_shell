#include "shell.h"

/**
 * build_env_var - builds the environment variable
 * @env_var: a pointer to environment variable
 * @name: the name of the environment variable
 * @value: the value of the environment variable
 */
void build_env_var(char *env_var, char *name, char *value)
{
	_strcpy(env_var, name);
	_strcat(env_var, "=");
	_strcat(env_var, value);
}

/**
 * free_node - frees struct envNode element
 * @node: a pointer to the node
 */
void free_node(envNode_t *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

/**
 * get_node_by_name - returns a value of environment variable
 * @head: a pointer to the first node of the list
 * @name: a name of the variable
 * Return: the value of the variable
 */
char *get_node_by_name(envNode_t *head, char *name)
{
	envNode_t *current = head;

	while (current != NULL)
	{
		if (_strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
