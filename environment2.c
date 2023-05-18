#include "shell.h"
/**
 * add_node_end - add a new element at the end of the list
 * @name : name of  the element
 * @value : value of the element 
 * Return : pointer to the new element
 */

envNode_t *add_node_end(envNode_t **head, char *name, char *value)
{
	envNode_t *new;
	envNode_t *current = *head;

	while (current && current->next != NULL)
	{
		current = current->next;
	}
	new = malloc(sizeof(envNode_t));
	if (!new)
	{
		return (NULL);
	}	
	new->name = _strdup(name);
	if (!new->name)
	{
		free(new);
		return (NULL);
	}
	new->value = _strdup(value);
	if (!new->value)
	{
		free(new->name);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	if (current)
		current->next = new;
	else
		*head = new;
	return (new);
}


envNode_t *convert_to_list(char **envp)
{
	char *var, *name, *value;
	envNode_t *list = NULL;

	while(*envp)
	{
		var = _strdup(*envp);
		if (!var)
		{
			return (NULL)
		}
		name = strtok(var, "=");
		value = strtok(NULL, "=");
		add_node_end(&list, name, value);
		envp++;
		free(var);
	}
	return (list);
}

void print_env_list(const envNode_t *envp)
{
	while (envp)
	{
		if (envp->name)
			write(STDOUT_FILENO, envp->name, _strlen(envp->name);
		write(STDOUT_FILENO, "=", 1);
		if (envp->value)
			write(STDOUT_FILENO, envp->value, _strlen(envp->value);
		write(STDOUT_FILENO, "\n", 1);
		envp = envp->next;
	}
}

int  _setenv(envNode_t µµhead, char *name, char *value, int overwrite)
{
	envNode_t *current = *head;
	/*search for the node with matching name*/
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			if (overwrite)
			{	
				free(current->value);
				current->value = _strdup(value);
				if (!current->value)
				{
					perror("not enough space");
					exit(-1);
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
		exit(-1);
	}
	return (0);
}
int list_len(envNode_t *list
	int len = 0;
	while (list)
	{
	len
