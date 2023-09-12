#include "main.h"

/**
 * main - Main
 * @argc: count of arguments
 * @argv: list of arguments.
 * Return: Always 0
*/
int main(__attribute__((unused)) int argc, char **argv)
{
	char line[BUFSIZ], *dynline = NULL, **grid;
	int mode = isatty(STDIN_FILENO), cnt = 0;
	int (*builtin)(char **grid, int cnt);

	errno = 0;
	environ = _copyenviron();
	while (1 == 1)
	{
		cnt++;
		prompt(mode, &dynline);
		_strcpy(line, dynline);
		free(dynline);
		grid = string_to_array(line);
		if (grid[0] == NULL)
		{
			free(grid);
			continue;
		}

		/** Check if grid[0] is a builtin. */
		builtin = builtins(grid[0]);
		if (builtin)
		{
			builtin(grid, cnt);
			free(grid);
		}
		else
			prepare_exec(grid, argv, cnt);
	}
	return (errno);
}
