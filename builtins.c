#include "main.h"

/**
 * builtins - shell builtins.
 * @s: string to compare.
 * Return: Always 0.
*/
int (*builtins(char *s))(char **grid, char *line)
{
	builtin_t sys[] = {
		{"exit", _exitshell},
		{"env", _printenv},
		{NULL, NULL}
	};
	int i = 0;

	while (sys[i].builtin)
	{
		if (_strcmp(sys[i].builtin, s) == 0)
			return (sys[i].f);
		i++;
	}

	return (NULL);
}

/**
 * _exitshell - exits shell.
 * @grid: list of arguments
 * @line: string passed into program.
 * Return: Always 0.
*/
int _exitshell(char **grid, __attribute__((unused)) char *line)
{
	free_grid(grid);
	free(environ);
	exit(errno);
}

/**
 * _printenv - prints env.
 * @grid: list of arguments
 * @line: string passed into program.
 * Return: Always 0.
*/
int _printenv(char **grid, __attribute__((unused)) char *line)
{
	int i;

	free(grid);
	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_putchar('\n');
	}
	return (0);
}
