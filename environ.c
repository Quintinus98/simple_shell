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
		env[i] = environ[i];
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
	int k = 0, len = 0, envl = 0;
	char *str = NULL, *sp;
	char **env = environ;

	if (!name || name[0] == '\0')
		return (NULL);

	len = _strlen(name);
	/** Get env matching name and = sign.*/
	while (*env != NULL)
	{
		if (_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			break;
		env++;
	}

	if (*env == NULL)
		return (NULL);

	sp = _strdup(*env);
	if (!sp)
		return (NULL);

	len++;
	envl = _strlen(sp);
	str = malloc((envl - len) * sizeof(char));
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
int _unsetenv(char *name)
{
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
	return (0);
}

/**
 * _setenv - sets an env
 * @name: Name of env to set
 * @value: value of name
 * @overwrite: 1 to overwrite 0 not to overwrite.
 * Return: Always 0.
*/
int _setenv(char *name, char *value, int overwrite)
{
	char *env, *envName;
	int err;

	/** Check if name, value = null, string name does not contain = */
	if (!name || _strchr(name, '=') != NULL || !value)
	{
		errno = EINVAL;
		return (-1);
	}
	/** name exists and do not overwrite */
	envName = _getenv(name);
	if (envName != NULL && overwrite == 0)
	{
		free(envName);
		return (0);
	}
	/** Remove name */
	err = _unsetenv(name);
	if (err == -1)
		return err;

	env = malloc(_strlen(name) + _strlen(value) + 2);
	if (!env)
		return (-1);

	_strcpy(env, name);
	_strcat(env, "=");
	_strcat(env, value);

	err = _putenv(env);
	if (err == -1)
		return err;
	return (0);
}

/** _putenv - Puts an env variable into environ
 * @env: environment variable
 * Return: 0 if successful or -1 if it fails.
*/
int _putenv(char *env)
{
	int len = 0, i = 0;
	char **new_env;

	while (environ[len])
		len++;

	new_env = _realloc(environ, len, (len + 2));
	if (!new_env)
		return (-1);
	for (i = 0; environ[i]; i++)
		new_env[i] = environ[i];
	free(environ);
	environ = new_env;
	environ[i] = env;
	environ[i + 1] = NULL;

	return (0);
}
