#include "main.h"

/**
 * main - Main
 * @argc: count of arguments
 * @argv: list of arguments.
 * Return: Always 0
*/
int main(__attribute__((unused)) int argc, char **argv)
{
	int mode = isatty(STDIN_FILENO), cnt = 0;
	char *line = NULL, **grid, *cmd = NULL;
	int (*builtin)(char **argv, char *line);

	errno = 0;
	while (1)
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
		if (access(grid[0], X_OK) == -1)
		{
			builtin = builtins(grid[0]);
			if (builtin)
			{
				builtin(grid, line);
				continue;
			}
			cmd = get_path_loc("PATH", grid[0]);
			if (cmd == NULL)
			{
				zerror(argv[0], cnt, grid[0]);
				free(grid);
				errno = 127;
				continue;
			}
			exec_cmd(grid, argv, cmd);
			continue;
		}
		/** If cmd is found {e.g /bin/ls} execute. */
		execute(grid, argv);
	}
	return (errno);
}
