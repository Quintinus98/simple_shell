#include "main.h"

/**
 * prompt - Displays "$ {User input}";
 * @mode: Determines if the $ sign will be printed.
 * @line: Address of line in main.
 * Return: Returns the entered user input.
*/

void prompt(int mode, char **line)
{
	size_t linecap = 0;
	ssize_t linelen;

	if (mode == 1)
		write(1, "$ ", 2);
	linelen = _getline(line, &linecap, stdin);
	if (linelen == -1)
	{
		exit(errno);
	}
}

/**
 * string_to_array - splits string
 * @s: array of string character.
 * @sep: seperator.
 * Return: an array of each word of the string.
*/
char **string_to_array(char *s, char *sep)
{
	int i = 0;
	char **arr, *token;

	/** Create Dynamic array */
	arr = malloc(30 * sizeof(char *));
	if (arr == NULL)
		return (NULL);

	/** Get Token and use for loop to extract the rest. */
	token = _strtok(s, sep);
	while (token != NULL)
	{
		arr[i] = token;
		token = _strtok(NULL, sep);
		i++;
	}
	arr[i] = NULL;

	return (arr);
}

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
