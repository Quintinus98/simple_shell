#include "main.h"

/**
 * builtins - shell builtins.
 * @s: string to compare.
 * Return: Always 0.
*/
int (*builtins(char *s))(char **grid, int cnt)
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
 * @cnt: count of program run.
 * Return: Always 0.
*/
int _exitshell(char **grid, int cnt)
{
	int status = errno;

	if (grid[1])
	{
		status = _atoi(grid[1]);
		if (status <= 0)
		{
			exitError(cnt, grid[1]);
			status = 2;
		}
	}

	free(grid);
	free(environ);
	exit(status);
}

/**
 * _printenv - prints env.
 * @grid: list of arguments
 * @cnt: count of program run.
 * Return: Always 0.
*/
int _printenv(char **grid, __attribute__((unused)) int cnt)
{
	int i;

	if (!environ)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_putchar('\n');
	}
	free(grid);
	return (0);
}
