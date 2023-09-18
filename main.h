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
	int (*f)(char **grid, int cnt, char **lg);
} builtin_t;

typedef struct env_list
{
	char *env_str;
	struct env_list *next;
} env_t;

typedef struct arraysub
{
	char **subarr;
	char *logOp;
	int pos;
} arraysub_t;

#define MAX_ELEM 10

/** essentials.c */
void prompt(int mode, char **line);
char **string_to_array(char *s, char *sep);
char check_ptr(char ch, char sh);
void update_arr(char **arr, char ch, int i);
int update_arr_tok(char **arr, char *token, int i);

/** execute.c */
int _exec(char **grid, char **argv, char *cmd);
void prepare_exec (char **grid, char **argv, int cnt);
void prepare_subgrid(char **grid, char **line_grid, int cnt, char **argv);

/** get_path_loc.c */
char *get_path_loc(char *path, char *cmd);

/** environ.c */
char **_copyenviron(void);
char **_getenv(char *name);
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
int (*builtins(char *s))(char **grid, int cnt, char **lg);
int _exitshell(char **grid, int cnt, char **lg, arraysub_t subgrid);
int _printenv(char **grid, int cnt, char **lg);
int _chdir(char **grid, int cnt, char **lg);
void _updatedir(char *mode, char *cur);

/** builtin_funcs.c*/
int _unsetenv(char **grid, int cnt, char **lg);
int _setenv(char **grid, int cnt, char **lg);


/** getline.c */
int _getline(char **linep, size_t *linecapp, FILE *stream);

/** strtok.c */
char *_strtok(char *str, char *sep);
int is_sep(char ch, char *sep);

/** errors.c */
void zerror(char *prog, int count, char *cmd);
void exitError(int count, char *val);
void cdError(char *cmd);

/** logicalOp.c */
arraysub_t getSubArray(char **arr, int i);
void freeSubArray(arraysub_t subArr);
char **string_to_arr(char *s, char *sep);

#endif
