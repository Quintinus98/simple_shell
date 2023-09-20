#include "main.h"

/**
 * builtins - shell builtins.
 * @s: string to compare.
 * Return: Always 0.
*/
int (*builtins(char *s))(char **grid, int cnt, alias_t **ls)
{
	builtin_t sys[] = {
		{"env", _printenv},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _chdir},
		{"alias", _alias},
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
 * @subgrid: sub grid.
 * Return: Always 0.
*/
int _exitshell(char **grid, int cnt, char **lg, arraysub_t subgrid)
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

	freeSubArray(subgrid);
	free(grid);
	free_grid(environ);
	free(lg);
	exit(status);
}

/**
 * _printenv - prints env.
 * @grid: list of arguments
 * @cnt: count of program run.
 * @ls: alias list
 * Return: Always 0.
*/
int _printenv(char **grid, int cnt, alias_t **ls)
{
	int i;
	char newline = '\n';

	(void)grid;
	(void)ls;
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
 * @ls: alias list
 * Return: On success zero (0).
*/
int _chdir(char **grid, __attribute__((unused)) int cnt, alias_t **ls)
{
	char **hm, dir[255], *str, **opwd = _getenv("OLDPWD"), **pwd = _getenv("PWD");

	(void)ls;
	if (grid[1] == NULL || _strcmp(grid[1], "~") == 0)
	{
		getcwd(dir, 255);
		hm = _getenv("HOME");
		if (!hm)
			return (0);
		_updatedir("OLDPWD=", dir);
		chdir(*hm + 5);
		_updatedir("PWD=", NULL);
	}
	else if (_strcmp(grid[1], "-") == 0)
	{
		getcwd(dir, 255);
		free(*pwd);
		*pwd = _strdup(*opwd + 3);
		free(*opwd);
		str = malloc((_strlen(dir) + 7));
		_strcpy(str, "OLDPWD=");
		_strcat(str, dir);
		*opwd = str;
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
