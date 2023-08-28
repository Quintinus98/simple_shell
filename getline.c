#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "errno.h"

int _getline(char **linep, size_t *linecapp, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/**
 * main - Executes function
 * @argc: count of arguments
 * @argv: list of arguments
 * Return: Always 0.
*/
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	printf("Start Line!\n\n");

	linelen = _getline(&line, &linecap, stdin);
	printf("%s\n", line);
	printf("%ld\n", linelen);

	free(line);

	return (0);
}

/**
 * _getline - Gets line from the terminal.
 * @linep: address of string line.
 * @linecapp: address of line capacity.
 * @stream: file stream.
 * Return: Length of line.
*/

int _getline(char **linep, size_t *linecapp, FILE *stream)
{
	char ch;
	char *str;
	size_t i = 0, new_size;

	(void)stream;
	if (linep == NULL || linecapp == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (stream != stdin)
	{
		fflush(stdin);
	}
	

	str = malloc((*linecapp = *linecapp + 1) * sizeof(char));
	while (read(STDIN_FILENO, &ch, 1) && ch != '\n' && ch != EOF && i < SSIZE_MAX)
	{
		str[i] = ch;
		if (i == (*linecapp - 1))
		{
			new_size = (*linecapp + 2);
			str = _realloc(str, *linecapp, new_size);
			*linecapp += 2;
		}
		i++;
	}
	if (ch == EOF || !str)
	{
		free(str);
		return (-1);
	}
	if (i == SSIZE_MAX)
	{
		free(str);
		errno = EOVERFLOW;
		return (-1);
	}

	str[i] = '\n';
	str[i++] = '\0';

	*linep = str;
	return (i);
}


/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: ptr is a pointer to the memory previously allocated
 * @old_size: the size, in bytes, of the allocated space for ptr
 * @new_size: the new size, in bytes of the new memory block
 *
 * Return: Nothing.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *ar, *tmp;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(new_size));

	ar = malloc(new_size);
	if (!ar)
		return (NULL);

	tmp = ptr;

	if (new_size > old_size)
		for (i = 0; i < old_size; i++)
			ar[i] = tmp[i];

	if (new_size < old_size)
		for (i = 0; i < new_size; i++)
			ar[i] = tmp[i];

	free(ptr);
	return (ar);
}
