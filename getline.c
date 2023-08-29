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
	char ch, *str;
	size_t i = 0, new_size;
	ssize_t val ;

	if (linep == NULL || linecapp == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	val = 0;
	(void)stream;
	// if (val == 0)
	// 	fflush(stream);
	// else
	// 	return (-1);

	str = malloc((*linecapp = *linecapp + 1) * sizeof(char));
	if (!str)
		return (-1);

	while (read(STDIN_FILENO, &ch, 1) != -1 && ch != '\n')
	{
		str[val] = ch;
		if (i == (*linecapp - 1))
		{
			new_size = (*linecapp + 2);
			str = _realloc(str, *linecapp, new_size);
			*linecapp += 2;
		}
		val++;
	}
	str[val] = '\n';
	str[val++] = '\0';
	*linep = str;

	return (val);
}
