#include "main.h"

/**
 * zerror - prints error message.
 * @prog: program name
 * @count: program count
 * @cmd: command
*/
void zerror(char *prog, int count, char *cmd)
{
	char cmdc = (count + '0');

	_puts(prog);
	_puts(": ");
	_putchar(cmdc);
	_puts(": ");
	_puts(cmd);
	_puts(": not found\n");
}

/**
 * free_grid - prints a grid of integers
 * @grid: grid
 *
 * Return: Nothing.
 */
void free_grid(char **grid)
{
	int h;

	for (h = 0; grid[h] != NULL; h++)
	{
		free(grid[h]);
	}
	free(grid);
}


/**
 * _strlen - length of string
 * @str: string
 * Return: Length of string.
*/
int _strlen(char *str)
{
	int cnt = 0;

	if (str == NULL)
		return (0);
	while (str[cnt] != '\0')
		cnt++;
	return (cnt);
}

/**
 * _strcmp - Compares two strings
 * @s1: string one
 * @s2: string two
 * Return: difference btw the two strings.
 */
int _strcmp(char *s1, char *s2)
{
	unsigned int diff = 0;

	while (*s1 != '\0')
	{
		diff = *s1 - *s2;
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}

	return (diff);
}

/**
 * _strdup - Duplicates a string.
 * @s: string
 * Return: A duplicate of string s.
*/
char *_strdup(char *s)
{
	int i = 0, len = _strlen(s);
	char *sdup;

	if (!s)
		return (NULL);
	sdup = malloc((len + 1) * sizeof(char));
	if (!sdup)
		return (NULL);
	for (i = 0; s && s[i]; i++)
		sdup[i] = s[i];
	sdup[i] = '\0';

	return (sdup);
}
