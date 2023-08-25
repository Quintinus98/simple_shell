#include "main.h"


/**
 * _strcat - String Concatenation fn
 * @dest: destinination
 * @src: Source
 *
 * Return: 0
 */
char *_strcat(char *dest, char *src)
{
	int cntdest = _strlen(dest);
	int cntSrc = _strlen(src);
	int total = cntdest + cntSrc;
	int i = 0;

	for (; cntdest < total; cntdest++)
	{
		dest[cntdest] = src[i];
		i++;
	}
	dest[total] = '\0';

	return (dest);
}

/**
 * _strchr - searches for the first occurrence of the character c in string s.
 * @s: string
 * @c: character
 * Return: pointer to the first occurrence of the character c in the string s.
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	return (NULL);
}

/**
 * _strcpy - String copy function
 * @dest: Destination variable
 * @src: Source variable
 *
 * Return: Returns a character.
 */
char *_strcpy(char *dest, char *src)
{
	int i, len;

	len = _strlen(src);
	for (i = 0; i < len; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _strncmp - Compares two strings
 * @s1: string one
 * @s2: string two
 * @n: compare n alphabets.
 * Return: difference btw the two strings.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int diff = 0, i = 0;

	if (n == 0)
		return (0);

	while (*s1 != '\0' && i < n)
	{
		diff = *s1 - *s2;
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		i++;
	}

	return (diff);
}

/**
 * _strncat - String Concatenation fn
 * @dest: destinination
 * @src: Source
 * @n: len
 * Return: 0
 */
char *_strncat(char *dest, char *src, size_t n)
{
	int cntdest = _strlen(dest);
	int total = cntdest + n;
	int i = 0;

	for (; cntdest < total && src[i] != '\0'; cntdest++)
	{
		dest[cntdest] = src[i];
		i++;
	}
	dest[total] = '\0';

	return (dest);
}
