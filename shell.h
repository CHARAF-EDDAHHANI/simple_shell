#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char *_strdup(char *str);
char **_strtok(char *str, const char *delim);
int tokenCount(char *str, const char *delim);
int isDelim(char c, const char *delim);
int _strlen(char *str);
int _strcmp(char *str1, const char *str2);
char *_strcat(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
int reallocate(char **lineptr, ssize_t n);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char *_memcpy(char *dest, char *src, size_t n);
char *_strncat(char *dest, char *src, size_t n);
char *_strchr(char *str, char c);

#endif /* SHELL_H */
