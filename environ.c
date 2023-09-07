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

char *_getenv(char *name)
{
	int k = 0, len = 0, i = 0;
	char *str = NULL, *sp = NULL;

	if (!name || name[0] == '\0')
		return (NULL);

	len = _strlen(name);
	/** Get env matching name and = sign.*/
	for (i = 0; environ[i] != NULL; i++)
		if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			sp = _strdup(environ[i]);

	if (!sp)
		return (NULL);

	len++;
	str = malloc((_strlen(sp) - len) * sizeof(char));
	if (!str)
		return (NULL);
	for (; sp[len + k] != '\0'; k++)
		str[k] = sp[len + k];
	str[k] = '\0';

	free(sp);
	/** Always remember to free str. */
	return (str);
}

/**
 * _unsetenv - Unsets an env
 * @name: Name of env to unset
 * Return: Always 0.
*/
int _unsetenv(char **grid, __attribute__((unused)) int cnt)
{
	char *name = grid[1];
	int len = _strlen(name);
	char **env = environ, **entries;

	/** Check if name = null, string name does not contain = */
	if (!name || _strchr(name, '=') != NULL || name[0] == '\0')
	{
		errno = EINVAL;
		return (-1);
	}

	while (*env != NULL)
	{
		/** Compare env with name for length len.*/
		/** for: continue loop. */
		if (_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			for (entries = env; *entries != NULL; entries++)
				*entries = *(entries + 1);
		else
			env++;
	}
	free(grid);
	return (0);
}

/**
 * _setenv - sets an env
 * @grid: array of commands
 * @cnt: count
 * Return: Always 0 if successful and -1 if not.
*/
int _setenv(char **grid, int cnt)
{
	int err;
	char *env, *val_from_name;
	char *name = grid[1], *value = grid[2];

	/** Check if name, value = null, string name does not contain = */
	if (!name || _strchr(name, '=') || !value)
	{
		errno = EINVAL;
		return (-1);
	}

	/** name exists, overwrite*/
	val_from_name = _getenv(name);
	if (val_from_name)
	{
		/** Remove name */
		err = _unsetenv(grid, cnt);
		if (err == -1)
			return (err);
	}

	env = malloc(_strlen(name) + _strlen(value) + 2);
	if (!env)
		return (-1);
	_strcpy(env, name);
	_strcat(env, "=");
	_strcat(env, value);

	err = _putenv(env);
	if (err == -1)
		return (err);

	if (!val_from_name)
		free(grid);

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
	environ[i + 1]= NULL;


	return (0);
}

/**
 echo "env
 setenv HBTN Holberton
 env" | ./hsh
*/
