#include "shell.h"

/**
 * _strchr - locate character in a string
 * @str: the giving string
 * @c: the character to be located
 * Return: a pointer to the matched character or NULL if not found
 */

char *_strchr(char *str, char c)
{
	if (!str)
		return (NULL);
	while (str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

/**
 * _strncat - appends n characters of src with desc string
 * @dest: the destination string
 * @src: the source string
 * @n: the number of character
 * Return: the pointer to the concatenate string
 */

char *_strncat(char *dest, char *src, size_t n)
{
	size_t d_len = 0, i;

	d_len = _strlen(dest);
	for (i = 0; i < n && src[i]; i++)
		dest[d_len + i] = src[i];
	dest[d_len + i] = '\0';
	return (dest);
}

/**
 * _memcpy - copy n characters from src to dest
 * @dest: destination pointer
 * @src: src pointer
 * @n: nbr of characters to be copied
 * Return: a pointer to copied memory
 */

char *_memcpy(char *dest, char *src, size_t n)
{
	char *newDest = dest;

	while (n--)
		*dest++ = *src++;
	return (newDest);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory
 * @old_size: old size of memory allocated
 * @new_size: new size of memory
 * Return: a pointer to the new allocated memory
 */

void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *newptr;

	if (new_size == old_size)
		return (ptr);
	if (!new_size && ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
	{
		newptr = malloc(new_size);
		if (!newptr)
		{
			perror("Error : malloc");
			return (NULL);
		}
		free(ptr);
		return (newptr);
	}
	newptr = malloc(new_size);
	if (!newptr)
	{
		perror("Error : malloc");
		return (NULL);
	}
	if (new_size > old_size)
		_memcpy(newptr, ptr, old_size);
	else
		_memcpy(newptr, ptr, new_size);
	free(ptr);
	return (newptr);
}


/**
 * reallocate - reallocate memory
 * @lineptr: a pointer to the line string
 * @n: the new size
 * Return: 1 (Success), 0 otherwize
 */

int reallocate(char **lineptr, ssize_t n)
{
	char *newLineptr;

	newLineptr = _realloc(*lineptr, _strlen(*lineptr), n);
	if (!newLineptr)
	{
		free(*lineptr);
		return (0);
	}
	*lineptr = newLineptr;
	return (1);
}
