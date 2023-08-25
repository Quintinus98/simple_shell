#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

/** Other important declarations*/
extern char **environ;
typedef struct builtin
{
	char *builtin;
	int (*f)(char **arg, char *line);
} builtin_t;

/** func1.c */
void prompt(int mode, char **line);
char **string_to_array(char *s);
char *get_path_loc(char *path, char *name);
char *_getenv(char *name);

/** func2.c */
int exec_cmd(char **arr, char **argv, char *cmd);
void execute(char **arr, char **argv);

/** aux_funcs1.c */
void zerror(char *prog, int count, char *cmd);
void free_grid(char **grid);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strdup(char *s);

/** aux_funcs2.c */
char *_strcat(char *dest, char *src);
char *_strchr(char *s, char c);
char *_strcpy(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strncat(char *dest, char *src, size_t n);

/** aux_funcs3.c */
void _puts(char *str);
int _putchar(char c);
char *_memcpy(char *dest, char *src, unsigned int n);

/** builtins.c */
int (*builtins(char *s))(char **argv, char *line);
int _exitshell(char **argv, char *line);
int _printenv(char **argv, char *line);

#endif

