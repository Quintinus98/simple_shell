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
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _chdir},
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
	free_grid(environ);
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

	(void)grid;
	if (!environ)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_putchar('\n');
	}

	return (0);
}

/**
 * _updatewd - Updates working directory
 * @mode: OLDPWD or PWD
 * @cur: current directory;
*/
void _updatewd(char *mode, char *cur)
{
	char **workdir;
	char *str;
	char dir[255];

	if (!cur)
		getcwd(dir, 255);
	else
		_strcpy(dir, cur);

	if (_strcmp(mode, "OLDPWD=") == 0)
		workdir = _getenv("OLDPWD");
	else
		workdir = _getenv("PWD");

	str = malloc((_strlen(dir) + _strlen(mode)));
	_strcpy(str, mode);
	_strcat(str, dir);
	free(*workdir);
	*workdir = str;
}

/**
 * _chdir - Changes directory
 * @grid: list of arguments
 * @cnt: count of program run.
 * Return: On success zero (0).
*/
int _chdir(char **grid, __attribute__((unused)) int cnt)
{
	char **home = NULL, previous[255], current[255];
	char **oldpwd = _getenv("OLDPWD"), **pwd = _getenv("PWD"), *str;

	if (grid[1] == NULL || _strcmp(grid[1], "~") == 0)
	{
		_updatewd("OLDPWD=", NULL);
		home = _getenv("HOME");
		chdir(*home + 5);
		_updatewd("PWD=", NULL);
	}
	else if (_strcmp(grid[1], "-") == 0)
	{
		getcwd(current, 255);
		free(*pwd);
		*pwd = _strdup(*oldpwd + 3);
		free(*oldpwd);
		str = malloc((_strlen(current) + 7));
		_strcpy(str, "OLDPWD=");
		_strcat(str, current);
		*oldpwd = str;

		chdir(*pwd + 4);
	}
	else
	{
		getcwd(previous, 255);
		if (chdir(grid[1]) == 0)
		{
			_updatewd("OLDPWD=", previous);
			_updatewd("PWD=", NULL);
		}
		else
		{
			cdError(grid[1]);
			return (-1);
		}
	}
	return (0);
}
