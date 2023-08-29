#include "main.h"

/**
 * _getline - Gets line from the terminal.
 * @linep: address of string line.
 * @linecapp: address of line capacity.
 * @stream: file stream.
 * Return: Length of line.
*/

int _getline(char **linep, size_t *linecapp, FILE *stream)
{
	char ch = '0', *str;
	ssize_t fd, st;
	static size_t val ;

	if (linep == NULL || linecapp == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (val == 0)
		fflush(stream);
	else
		return (-1);

	str = malloc((*linecapp = *linecapp + 1) * sizeof(char));
	if (!str)
		return (-1);

	while (ch != '\n')
	{
		fd = read(STDIN_FILENO, &ch, 1);
		if (fd == -1 || (fd == 0 && val == 0))
		{
			free(str);
			return (-1);
		}
		
		str[val] = ch;
		if (val == (*linecapp - 1))
		{
			str = _realloc(str, *linecapp, *linecapp + 2);
			*linecapp += 2;
		}
		val++;
	}
	str[val] = '\n';
	str[val++] = '\0';
	*linep = str;

	st = val;
	if (st != 0)
		val = 0;

	return (st);
}
