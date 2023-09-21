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

	write(STDERR_FILENO, prog, _strlen(prog));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmdc, _strlen(cmdc));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);

	free(cmdc);
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
	write(STDERR_FILENO, "./hsh: cd: ", 11);
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, ": No such file or directory\n", 28);

	errno = 1;
}
