#include "main.h"

/**
 * exec_cmd - Execute with full command path.
 * @arr: dynamically allocated array
 * @argv: list of command arguments
 * @cmd: command path.
 * Return: Always 0
*/
int exec_cmd(char **arr, char **argv, char *cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror(cmd);
		exit(-1);
	}
	else if (child_pid == 0)
	{
		execve(cmd, arr, environ);
		perror(argv[0]);
		exit(2);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		errno = status;
		free(cmd);
		free(arr);
	}
	return (status);
}

/**
 * execute - Execute with full command path.
 * @arr: dynamically allocated array
 * @argv: list of command arguments
*/
void execute(char **arr, char **argv)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror(argv[0]);
		exit(-1);
	}
	else if (child_pid == 0)
	{
		execve(arr[0], arr, environ);
		perror(argv[0]);
		exit(2);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		errno = status;
		free(arr);
	}
}
