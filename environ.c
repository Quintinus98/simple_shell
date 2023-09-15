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
