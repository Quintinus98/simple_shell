#include "main.h"

/**
 * _puts - Puts string
 * @str: str is a char
 */

void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}

/**
 * _putchar - Writes the character c to stdout
 * @c: The character to print
 * Return: On success 1
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
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

/**
 * _itoa - constructs a string representation of an integer.
 * @value: integer value.
 * Return: String representation.
*/
char *_itoa(int value)
{
	char *buffer;
	int len = ilen(value), i;

	buffer = malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);

	for (i = (len - 1); i >= 0; i--)
	{
		buffer[i] = (value % 10) + '0';
		value /= 10;
	}
	buffer[len] = '\0';
	return (buffer);
}
