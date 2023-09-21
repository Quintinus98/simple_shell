#include "main.h"

/**
 * main - Main
 * @argc: count of arguments
 * @argv: list of arguments.
 * Return: Always 0
*/
int main(__attribute__((unused)) int argc, char **argv)
{
	char line[BUFSIZ], *dynline = NULL, **grid = NULL;
	int mode = isatty(STDIN_FILENO), cnt = 0, i = 0;
	char **line_grid = NULL, *line_sep = ";", *sep = " \n";
	alias_t *aliasList = NULL;

	errno = 0;
	while (1 == 1)
	{
		prompt(mode, &dynline);
		_strcpy(line, dynline);
		free(dynline);

		comments(line);
		line_grid = string_to_arr(line, line_sep);
		for (i = 0; line_grid[i]; i++)
		{
			cnt++;

			grid = string_to_array(line_grid[i], sep);
			if (grid[0] == NULL)
			{
				free(grid);
				continue;
			}

			prepare_subgrid(grid, line_grid, cnt, argv, &aliasList);

			free(grid);
		}
		free(line_grid);
	}
	return (errno);
}
