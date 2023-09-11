#include "main.h"

/**
 * _copyenviron - Copies environ
 * Return: A copy of environ.
*/
char **_copyenviron(void)
{
	char **env;
	int len = 0, i = 0;

	while (environ[len])
		len++;

	env = malloc((len + 1) * sizeof(char *));
	if (!env)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		env[i] = malloc((_strlen(environ[i]) + 1) * sizeof(char));
		if (!env[i])
		{
			for (i--; i >= 0; i--)
				free(env[i]);
			free(env);
			return (NULL);
		}
		_strcpy(env[i], environ[i]);
	}
	env[i] = NULL;

	return (env);
}

/**
 * _getenv - gets an environment variable
 * @name: Name of env var to get.
 * Return: Environment variable.
*/

char **_getenv(char *name)
{
	int len = 0, i = 0;

	if (!name || name[0] == '\0')
		return (NULL);

	len = _strlen(name);
	/** Get env matching name and = sign.*/
	for (i = 0; environ[i] != NULL; i++)
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i]);

	return (NULL);
}

/**
 * _setenv - sets an env
 * @grid: array of commands
 * @cnt: count
 * Return: Always 0 if successful and -1 if not.
*/
int _setenv(char **grid, int cnt)
{
	char *env, **val_from_name = NULL, *name = grid[1], *value = grid[2];

	(void)cnt;
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
 * _putenv - Puts an env variable into environ
 * @env: environment variable
 * Return: 0 if successful or -1 if it fails.
*/
int _putenv(char *env)
{
	int len = 0, i = 0;
	char **new_environ;

	while (environ[len])
		len++;

	new_environ = malloc((len + 2) * sizeof(char *));
	if (!new_environ)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = environ[i];
	}
	free(environ);
	environ = new_environ;
	environ[i] = env;
	environ[i + 1] = NULL;


	return (0);
}

/**
 * _unsetenv - Unsets an env
 * @grid: Grid of values
 * @cnt: Number of times program has been executed.
 * Return: Always 0.
*/
int _unsetenv(char **grid, __attribute__((unused)) int cnt)
{
	char **env = environ, **new_environ, *name = grid[1], **temp;
	int len = _strlen(name), i, j;

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
