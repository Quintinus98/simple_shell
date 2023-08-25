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
 * _memcpy - Copies memory area
 * @dest: Destination
 * @src: Source memory area
 * @n: Copies
 *
 * Return: 0
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	char *destAdd = dest;
	unsigned int i = 0;

	for (; i < n; i++)
	{
		*dest = *src;
		src++;
		dest++;
	}
	dest = destAdd;

	return (dest);
}
