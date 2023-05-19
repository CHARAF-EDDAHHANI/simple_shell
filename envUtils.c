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
	free(node->name);
	free(node->value);
	free(node);
}
