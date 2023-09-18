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
	int mode = isatty(STDIN_FILENO), cnt = 0, i = 0;
	char **line_grid, *line_sep = ";", *sep = " \n";

	errno = 0;
	environ = _copyenviron();
	while (1 == 1)
	{
		prompt(mode, &dynline);
		_strcpy(line, dynline);
		free(dynline);

		line_grid = string_to_array(line, line_sep);
		for (i = 0; line_grid[i]; i++)
		{
			cnt++;

			grid = string_to_array(line_grid[i], sep);
			if (grid[0] == NULL)
			{
				free(grid);
				continue;
			}

			prepare_subgrid(grid, line_grid, cnt, argv);

			free(grid);
		}
		free(line_grid);
	}
	return (errno);
}
