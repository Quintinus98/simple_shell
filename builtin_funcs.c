#include "main.h"

/**
 * _setenv - sets an env
 * @grid: array of commands
 * @cnt: count
 * @lg: line grid
 * Return: Always 0 if successful and -1 if not.
*/
int _setenv(char **grid, int cnt, char **lg)
{
	char *env, **val_from_name = NULL, *name = grid[1], *value = grid[2];

	(void)cnt;
	(void)lg;
	if (!name || _strchr(name, '=') || !value)
	{
		errno = EINVAL;
		return (-1);
	}
	/** get address from env.*/
	val_from_name = _getenv(name);
	if (val_from_name != NULL && _strcmp(*val_from_name, value) == 0)
		return (0);

	env = malloc(_strlen(name) + _strlen(value) + 2);
	if (!env)
		return (-1);

	_strcpy(env, name);
	_strcat(env, "=");
	_strcat(env, value);

	if (val_from_name)
	{
		free(*val_from_name);
		*val_from_name = env;
	}
	else
		_putenv(env);

	return (0);
}



/**
 * _unsetenv - Unsets an env
 * @grid: Grid of values
 * @cnt: Number of times program has been executed.
 * @lg: line grid
 * Return: Always 0.
*/
int _unsetenv(char **grid, int cnt, char **lg)
{
	char **env = environ, **new_environ, *name = grid[1], **temp;
	int len = _strlen(name), i, j;

	(void)cnt;
	(void)lg;
	/** Check if name = null, string name does not contain = */
	for (i = 0; environ[i]; i++)
		;
	new_environ = malloc((i) * sizeof(char *));
	if (!name || _strchr(name, '=') != NULL || !new_environ)
	{
		errno = EINVAL;
		return (-1);
	}

	temp = _getenv(name);
	if (temp == NULL)
		return (0);

	for (i = 0, j = 0; env[i] != NULL; i++)
	{
		if (_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			free(env[i]);
			continue;
		}
		new_environ[j] = env[i];
		j++;
	}
	free(environ);
	environ = new_environ;
	environ[j] = NULL;

	return (0);
}
