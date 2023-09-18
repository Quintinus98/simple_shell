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
	int (*builtin)(char **grid, int cnt, char **lg);
	char **line_grid, *line_sep = ";", *sep = " \n";
	arraysub_t subgrid;
	int pos;

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

			subgrid = getSubArray(grid, 0);
			while (subgrid.subarr)
			{
				if (_strcmp(subgrid.subarr[0], "exit") == 0)
					_exitshell(grid, cnt, line_grid, subgrid);

				builtin = builtins(grid[0]);
				if (builtin)
					builtin(subgrid.subarr, cnt, line_grid);
				else
					prepare_exec(subgrid.subarr, argv, cnt);

				if (subgrid.logOp != NULL)
				{
					if (!_strcmp(subgrid.logOp, "&&") && errno != 0)
						break;
					if (!_strcmp(subgrid.logOp, "||") && errno == 0)
						break;
				}

				pos = subgrid.pos;
				freeSubArray(subgrid);
				subgrid = getSubArray(grid, pos);
			}
			free(grid);
		}
		free(line_grid);
	}
	return (errno);
}
