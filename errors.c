#include "main.h"

/**
 * zerror - prints error message.
 * @prog: program name
 * @count: program count
 * @cmd: command
*/
void zerror(char *prog, int count, char *cmd)
{
	char *cmdc = _itoa(count);
	size_t len = _strlen(prog) + _strlen(cmd) + ilen(count) + 16;
	char *err_msg = malloc(len * sizeof(char));

	if (!err_msg)
		return;
	_strcpy(err_msg, prog);
	_strcat(err_msg, ": ");
	_strcat(err_msg, cmdc);
	_strcat(err_msg, ": ");
	_strcat(err_msg, cmd);
	_strcat(err_msg, ": not found\n");

	write(STDERR_FILENO, err_msg, len);
	free(cmdc);
	free(err_msg);
	errno = 127;
}


/**
 * exitError - prints error message.
 * @count: program count
 * @val: value of error.
*/
void exitError(int count, char *val)
{
	char *cmdc = _itoa(count);
	size_t len = _strlen(val) + ilen(count) + 32;
	char *err_msg = malloc(len * sizeof(char));

	if (!err_msg)
		return;
	_strcpy(err_msg, "./hsh: ");
	_strcat(err_msg, cmdc);
	_strcat(err_msg, ": exit: Illegal number: ");
	_strcat(err_msg, val);
	_strcat(err_msg, "\n");

	write(STDERR_FILENO, err_msg, len);
	free(cmdc);
	free(err_msg);
}

/**
 * cdError - prints cd error
 * @cmd: cmd that failed;
*/
void cdError(char *cmd)
{
	write(1, "cd: no such file or directory: ", 31);
	write(1, cmd, _strlen(cmd));
	write(1, "\n", 1);
}
