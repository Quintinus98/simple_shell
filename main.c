#include "main.h"

/**
 * main - Main
 * @argc: count of arguments
 * @argv: list of arguments.
 * Return: Always 0
*/
int main(int argc, char **argv)
{
	int mode = isatty(STDIN_FILENO);
	int cnt = 0;
	char *line = NULL, **grid;
	char *ch = "$ ", *cmd = NULL;

	errno = 0;
	(void)argc;
	while (1)
	{
		cnt++;
		if (mode == 1)
			write(1, ch, 2);

		line = prompt();
		grid = string_to_array(line);
		if (grid == NULL)
			continue;

		if (access(grid[0], X_OK) == -1)
		{
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
		execute(grid, argv);
	}
	return (errno);
}
