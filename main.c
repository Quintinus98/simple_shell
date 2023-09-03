#include "main.h"

/**
 * main - Main
 * @argc: count of arguments
 * @argv: list of arguments.
 * Return: Always 0
*/
int main(__attribute__((unused)) int argc, char **argv)
{
	char *line = NULL, **grid;
	int mode = isatty(STDIN_FILENO), cnt = 0;
	int (*builtin)(char **argv, char *line);

	errno = 0;
	environ = _copyenviron();
	while (1 == 1)
	{
		cnt++;
		prompt(mode, &line);
		grid = string_to_array(line);
		if (grid[0] == NULL)
		{
			free(grid);
			continue;
		}

		/** If cmd is not found e.g ls */
		builtin = builtins(grid[0]);
		if (builtin)
		{
			builtin(grid, line);
			continue;
		}

    prepare_exec(grid, argv, cnt);
		free(line);
	}
	return (errno);
}
