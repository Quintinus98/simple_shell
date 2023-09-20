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
 * @ls: alias list
 * Return: Always 0
*/
void prepare_exec(char **grid, char **argv, int cnt, alias_t **ls)
{
	char *cmd = NULL;
	int flag = 0;
	alias_t *tmp = *ls;

	cmd = grid[0];
	for (; tmp != NULL; tmp = tmp->next)
		if (!_strcmp(tmp->name, cmd))
			cmd = tmp->val;

	if (access(cmd, X_OK) == 0 && _strcmp(cmd, "hbtn_ls") == 0 && grid[1])
	{
		_exec(grid, argv, cmd);
		return;
	}

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_path_loc("PATH", cmd);
	}

	if (!cmd || (access(cmd, X_OK) == -1))
	{
		zerror(argv[0], cnt, cmd);
	}
	else
	{
		_exec(grid, argv, cmd);
		if (flag)
			free(cmd);
	}
}

/**
 * prepare_subgrid - Prepares subgrid
 * @grid: grid
 * @lg: Line grid
 * @cnt: count
 * @av: list argument
 * @ls: alias list
*/
void prepare_subgrid(char **grid, char **lg, int cnt, char **av, alias_t **ls)
{
	arraysub_t subgrid;
	int pos;
	int (*builtin)(char **grid, int cnt, alias_t **ls);

	subgrid = getSubArray(grid, 0);
	while (subgrid.subarr)
	{
		if (_strcmp(subgrid.subarr[0], "exit") == 0)
			_exitshell(grid, cnt, lg, subgrid);

		builtin = builtins(grid[0]);
		if (builtin)
			builtin(subgrid.subarr, cnt, ls);
		else
			prepare_exec(subgrid.subarr, av, cnt, ls);

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
}
