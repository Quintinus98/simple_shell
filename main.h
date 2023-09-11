#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

/** Other important declarations*/
extern char **environ;
typedef struct builtin
{
	char *builtin;
	int (*f)(char **grid, int cnt);
} builtin_t;

typedef struct env_list
{
	char *env_str;
	struct env_list *next;
} env_t;

/** essentials.c */
void prompt(int mode, char **line);
char **string_to_array(char *s);
char *get_path_loc(char *path, char *name);

/** execute.c */
int _exec(char **grid, char **argv, char *cmd);
void prepare_exec (char **grid, char **argv, int cnt);

/** environ.c */
char **_copyenviron(void);
char **_getenv(char *name);
int _unsetenv(char **grid, int cnt);
int _setenv(char **grid, int cnt);
int _putenv(char *env);

/** aux_funcs1.c */
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
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_itoa(int value);
int _atoi(char *s);

/** aux_funcs4.c */
int ilen(int n);

/** builtins.c */
int (*builtins(char *s))(char **grid, int cnt);
int _exitshell(char **grid, int cnt);
int _printenv(char **grid, int cnt);
int _chdir(char **grid, int cnt);
void _updatewd(char *mode, char *cur);

/** getline.c */
int _getline(char **linep, size_t *linecapp, FILE *stream);

/** strtok.c */
char *_strtok(char *str, char *sep);
int is_sep(char ch, char *sep);

/** errors.c */
void zerror(char *prog, int count, char *cmd);
void exitError(int count, char *val);
void cdError(char *cmd);

#endif
