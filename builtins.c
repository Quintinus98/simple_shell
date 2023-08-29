#include "main.h"

/**
 * builtins - shell builtins.
 * @s: string to compare.
 * Return: Always 0.
*/
int (*builtins(char *s))(char **argv, char *line)
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
 * @argv: list of arguments
 * @line: string passed into program.
 * Return: Always 0.
*/
int _exitshell(char **argv, char *line)
{
	(void)line;
	free_grid(argv);
	exit(errno);
	return (errno);
}

/**
 * _printenv - prints env.
 * @argv: list of arguments
 * @line: string passed into program.
 * Return: Always 0.
*/
int _printenv(char **argv, char *line)
{
	int i;

	free(argv);
	(void)line;
	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_putchar('\n');
	}
	free(environ);
	return (0);
}
