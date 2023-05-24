#include "shell.h"

/**
 * add_node_end - add a new element at the end of the list
 * @head: a pointer to a pointers to environement vars
 * @name: name of  the element
 * @value: value of the element
 * Return: pointer to the new element
 */

Node_t *add_node_end(Node_t **head, char *name, char *value)
{
	Node_t *new;
	Node_t *current = *head;

	while (current && current->next != NULL)
		current = current->next;
	new = malloc(sizeof(Node_t));
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
 * free_node - frees struct envNode element
 * @node: a pointer to the node
 */

void free_node(Node_t *node)
{
	if (node->name)
		free(node->name);
	if (node->value)
		free(node->value);
	free(node);
}

/**
 * convert_to_list - converts the environ array to list
 * @envp: a pointer to an array of pointer to environment vars
 * Return: the first element of the list
 */

Node_t *convert_to_list(char **envp)
{
	char *var, *name, *value;
	Node_t *list = NULL;

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
