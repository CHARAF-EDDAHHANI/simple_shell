#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>



extern char **environ;

/**
 *  * struct envNode - Struct environment variable
 *   * @name: the environment name
 *    * @value: the envirornment value
 *     * @next: a pointer to the next node
 *      */

typedef struct Node
{
		char *name;
			char *value;
				struct Node *next;
} Node_t;


int _strlen(char *str);
int isDelim(char c, const char *delim);
int tokenCount(char *str, const char *delim);
char **_strtok(char *str, const char *delim);
char *_strdup(char *str);
char *_strchr(char *str, char c);
char *_strncat(char *dest, char *src, size_t n);
char *_memcpy(char *dest, char *src, size_t n);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
int reallocate(char **lineptr, ssize_t n);
char *_strcpy(char *dest, char *src);
char *_strcat(char *str1, char *str2);
int _strcmp(char *str1, const char *str2);
void free_list(char **ptr, int i);
int array_len(char **args);
int _atoi(char *s);
int _isdigit(int c);
void sigign(int signal);
char **parse_input(char *lineptr);
void print_prompt(void);
void free_args(char **av);
int execmd(char *exe, char **av, char **e);
void print_error(char *exe, char *desc);


#endif
