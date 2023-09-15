#include "main.h"

/**
 * builtins - shell builtins.
 * @s: string to compare.
 * Return: Always 0.
*/
int (*builtins(char *s))(char **grid, int cnt, char **lg)
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
 * @lg: line grid - Multi line grid.
 * Return: Always 0.
*/
int _exitshell(char **grid, int cnt, char **lg)
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
	free(lg);
	exit(status);
}

/**
 * _printenv - prints env.
 * @grid: list of arguments
 * @cnt: count of program run.
 * @lg: line grid - Multi line grid.
 * Return: Always 0.
*/
int _printenv(char **grid, int cnt, char **lg)
{
	int i;
	char newline = '\n';

	(void)grid;
	(void)lg;
	(void)cnt;
	if (!environ)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, &newline, 1);
	}

	return (0);
}

/**
 * _updatedir - Updates working directory
 * @mode: OLDPWD or PWD
 * @cur: current directory;
*/
void _updatedir(char *mode, char *cur)
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
 * @lg: line grid - Multi line grid.
 * Return: On success zero (0).
*/
int _chdir(char **grid, __attribute__((unused)) int cnt, char **lg)
{
	char **home = NULL, dir[255], *str;
	char **oldpwd = _getenv("OLDPWD"), **pwd = _getenv("PWD");

	(void)lg;
	if (grid[1] == NULL || _strcmp(grid[1], "~") == 0)
	{
		getcwd(dir, 255);
		home = _getenv("HOME");
		if (!home)
			return (0);
		_updatedir("OLDPWD=", dir);
		chdir(*home + 5);
		_updatedir("PWD=", NULL);
	}
	else if (_strcmp(grid[1], "-") == 0)
	{
		getcwd(dir, 255);
		free(*pwd);
		*pwd = _strdup(*oldpwd + 3);
		free(*oldpwd);
		str = malloc((_strlen(dir) + 7));
		_strcpy(str, "OLDPWD=");
		_strcat(str, dir);
		*oldpwd = str;

		chdir(*pwd + 4);
	}
	else
	{
		getcwd(dir, 255);
		if (chdir(grid[1]) == 0)
		{
			_updatedir("OLDPWD=", dir);
			_updatedir("PWD=", NULL);
		}
		else
		{
			cdError(grid[1]);
			return (-1);
		}
	}
	return (0);
}
