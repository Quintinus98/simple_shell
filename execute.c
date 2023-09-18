#include "main.h"

/**
 * _exec - Execute with full command path.
 * @grid: dynamically allocated array
 * @argv: list of command arguments
 * @cmd: command path.
 * Return: Always 0
*/
int _exec(char **grid, char **argv, char *cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		/** Something went wrong. */
		perror(cmd);
		exit(-1);
	}
	else if (child_pid == 0)
	{
		/** Child execute first. */
		execve(cmd, grid, environ);
		perror(argv[0]);
		exit(2);
	}
	else
	{
		/** Parent wait for child to execute. */
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		errno = status;
	}
	return (status);
}

/**
 * prepare_exec - Prepares execution.
 * @grid: dynamically allocated array
 * @argv: list of command arguments
 * @cnt: count of iterations.
 * Return: Always 0
*/
void prepare_exec(char **grid, char **argv, int cnt)
{
	char *cmd = NULL;
	int flag = 0;


	cmd = grid[0];
	if (access(cmd, X_OK) == 0 && _strcmp(cmd, "hbtn_ls") == 0 && grid[1])
	{
		_exec(grid, argv, cmd);
		return;
	}

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_path_loc("PATH", grid[0]);
	}

	if (!cmd || (access(cmd, X_OK) == -1))
	{
		zerror(argv[0], cnt, grid[0]);
	}
	else
	{
		_exec(grid, argv, cmd);
		if (flag)
			free(cmd);
	}
}
