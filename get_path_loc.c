#include "main.h"


/**
 * get_path_loc - Gets path location.
 * @path: Name of path.
 * @cmd: command to find.
 * Return: path location.
*/
char *get_path_loc(char *path, char *cmd)
{
	char *paths, **dir, *token, *command;
	struct stat st;

	dir = _getenv(path);
	if (!dir)
		return (NULL);

	paths = _strdup(*dir);
	token = _strtok(paths, ":");
	for (; token != NULL; token = _strtok(NULL, ":"))
	{
		command = malloc(_strlen(cmd) + _strlen(token) + 2);
		if (!command)
			return (NULL);

		_strcpy(command, token);
		_strcat(command, "/");
		_strcat(command, cmd);

		if (stat(command, &st) == 0)
		{
			free(paths);
			return (command);
		}
		free(command);
	}
	free(paths);
	return (NULL);
}
