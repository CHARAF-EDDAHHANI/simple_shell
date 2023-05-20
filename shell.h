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

/**
 * struct buildin - Struct build-in commands
 *
 * @cmd: The build-in command
 * @func: the function associated
 */
typedef struct buildin
{
	char *cmd;
	int (*func)(int argc, char **args, char ***e);
} buildin_t;

/**
 * struct envNode - Struct environment variable
 * @name: the environment name
 * @value: the envirornment value
 * @next: a pointer to the next node
 */
typedef struct envNode
{
	char *name;
	char *value;
	struct envNode *next;
} envNode_t;

extern char **environ;

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
int execmd(int argc, char **argv, char ***e);
int count_token(char *lineptr, const char *delim);
char **parse_input(char *execName, char *lineptr);
void buildPath(char *dirPath, char *cmd, char *path);
char *_which(char *cmd, char *envPath);
char *_getenv(const char *name);
char *build_error(char *exe, char *cmd, char *errorDesc);
void sigign(int signal);
char *_getenv2(const char *name, char **e);
char *build_error2(char *exe, char *cmd);
void free_list(char **ptr, int i);
int (*get_buildin_func(char *c))(int argc, char **args, char ***e);
int my_exit(int argc, char **args, char ***e);
int my_env(int argc, char **args, char ***e);
void free_node(envNode_t *node);
void build_env_var(char *env_var, char *name, char *value);
int list_len(envNode_t *list);
void print_env_list(const envNode_t *envp);
void _unsetenv(envNode_t **head, char *name);
char **list_to_environ(envNode_t *head);
int _setenv(envNode_t **head, char *name, char *value, int overwrite);
envNode_t *convert_to_list(char **envp);
envNode_t *add_node_end(envNode_t **head, char *name, char *value);
int set_env(int argc, char **args, char ***e);
int array_len(char **args);
int unset_env(int argc, char **args, char ***e);
char *get_node_by_name(envNode_t *head, char *name);
int my_cd(int argc, char **args, char ***e);

#endif /* SHELL_H */
