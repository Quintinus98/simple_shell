#include "main.h"

/**
 * prompt - Displays "$ {User input}";
 * Return: Returns the entered user input.
*/
char *prompt(void)
{
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	linelen = getline(&line, &linecap, stdin);
	if (linelen == -1)
		exit(errno);

	line[linelen - 1] = '\0';
	if (_strcmp(line, "\n") == 0)
		line = NULL;
	return (line);
}

/**
 * string_to_array - splits string
 * @s: array of string character.
 * Return: an array of each word of the string.
*/
char **string_to_array(char *s)
{
	int cnt = 0, i = 0;
	char **arr, *token, *tok, *scpy;
	const char *sep = " \n";

	/** Get Word Count */
	scpy = malloc(_strlen(s) * sizeof(char));
	if (!scpy || !s)
		return (NULL);
	_strcpy(scpy, s);
	tok = strtok(s, sep);
	for (; tok != NULL; tok = strtok(NULL, sep))
		cnt++;
	free(s);

	/** Create Dynamic array */
	arr = malloc((cnt + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);

	/** Get Token and use for loop to extract the rest. */
	token = strtok(scpy, sep);
	for (i = 0; token != NULL; i++)
	{
		arr[i] = malloc(_strlen(token) * sizeof(char));
		if (arr[i] == NULL)
		{
			free_grid(arr);
			return (NULL);
		}
		arr[i] = _strdup(token);
		token = strtok(NULL, " ");
	}
	arr[i] = NULL;

	free(scpy);
	return (arr);
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
 * get_path_loc - Gets path location.
 * @path: Name of path.
 * @cmd: command to find.
 * Return: path location.
*/
char *get_path_loc(char *path, char *cmd)
{
	char *paths, *token, *command;
	struct stat st;

	paths = _getenv(path);
	if (!paths)
		return (NULL);

	token = strtok(paths, ":");
	for (; token != NULL; token = strtok(NULL, ":"))
	{
		command = malloc(_strlen(cmd) + _strlen(token) + 2);
		if (!command)
			return (NULL);

		_strcpy(command, token);
		_strcat(command, "/");
		_strcat(command, cmd);

		if (stat(command, &st) == 0)
			return (command);
		free(command);
	}
	free(paths);
	return (NULL);
}
