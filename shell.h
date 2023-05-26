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
 * struct Node - Struct environment variable
 * @name: the environment name
 * @value: the envirornment value
 * @next: a pointer to the next node
 */

typedef struct Node
{
	char *name;
	char *value;
	struct Node *next;
} Node_t;

/**
 * struct buildin - Struct build-in commands
 * @cmd: The build in command
 * @func: the function associated
 */

typedef struct buildin
{
	char *cmd;
	int (*func)(char *exe, int ac, char **av, char **e, int s, int l);
} buildin_t;


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
char **parse_input(char *lineptr, char **e, int s);
void print_prompt(void);
void free_args(char **av);
int execmd(char *exe, char **av, char **e, int *flag, int *lvl);
void print_error(char *exe, char *desc);
void buildPath(char *dirPath, char *cmd, char *path);
char *_which(char *cmd, char *envPath);
char *_getenv(const char *name, char **e);
int print_cmd_not_found(char *exe, char **av, int l);
void execute_exit(int status, char **av, char *line, char **cmd);
void ignore_comments(char *lineptr);
void free_node(Node_t *node);
int replace_variables(char **args, char **e, int s);
char **parse_multi_cmd(char *lineptr);
char *convert_number(int n, int base, int upper_o_n);

/* Buildin functions */
int my_env(char *exe, int ac, char **as, char **e, int s, int l);
int my_exit(char *exe, int ac, char **as, char **e, int s, int l);
int (*get_func(char *c))(char *x, int a, char **v, char **e, int s, int l);



#endif
