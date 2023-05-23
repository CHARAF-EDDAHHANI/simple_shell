#include "shell.h"

/**
 * _strcpy - copies a string to a buffer
 * @src: a pointer to the source string
 * @dest: a pointer to the destination string
 * Return: pointer to the destination buffer
 */

char *_strcpy(char *dest, char *src)
{
	int srclen = 0, i;

	srclen = _strlen(src);

	for (i = 0; i <= srclen; i++)
		dest[i] = src[i];
	return (dest);
}

/**
 * _strcat - concatenates two strings
 * @str1: the first string
 * @str2: the second string
 * Return: the concatenate string
 */
char *_strcat(char *str1, char *str2)
{
	int len1 = 0, len2 = 0, i, j;

	len1 = _strlen(str1);
	len2 = _strlen(str2);

	for (i = 0, j = len1; i < len2; i++, j++)
		str1[j] = str2[i];
	str1[j] = '\0';
	return (str1);
}

/**
 * _strcmp - compares two strings
 * @str1: the first String
 * @str2: the second String
 * Return: 0 (if str1 and str2 equal), integer < 0 (if str1 less than str2)
 * integer > 0 (if str1 greater than str2)
 */
int _strcmp(char *str1, const char *str2)
{
	int i = 0, diff = 0;

	while (str1[i] && str2[i])
	{
		diff = str1[i] - str2[i];
		if (diff != 0)
			return (diff);
		i++;
	}
	diff = str1[i] - str2[i];
	return (diff);
}

/**
 * free_list - free an array of string
 * @ptr: the giving array to be freed
 * @i: the last index of the array
 */
void free_list(char **ptr, int i)
{
	while (i > 0)
		free(ptr[--i]);
	free(ptr);
}

/**
 * array_len - returns the length of an array of pointers
 * @args: a pointer of pointers to arguments
 * Return: the number of arguments
 */
int array_len(char **args)
{
	int len = 0;

	while (*args != NULL)
	{
		len++;
		args++;
	}
	return (len);
}
