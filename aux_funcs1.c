#include "main.h"


/**
 * _strlen - length of string
 * @str: string
 * Return: Length of string.
*/
int _strlen(char *str)
{
	int cnt = 0;

	if (str == NULL)
		return (0);
	while (str[cnt] != '\0')
		cnt++;
	return (cnt);
}

/**
 * _strcmp - Compares two strings
 * @s1: string one
 * @s2: string two
 * Return: difference btw the two strings.
 */
int _strcmp(char *s1, char *s2)
{
	unsigned int diff = 0;

	while (*s1 != '\0')
	{
		diff = *s1 - *s2;
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}

	return (diff);
}

/**
 * _strdup - Duplicates a string.
 * @s: string
 * Return: A duplicate of string s.
*/
char *_strdup(char *s)
{
	int i = 0, len = _strlen(s);
	char *sdup;

	if (!s)
		return (NULL);
	sdup = malloc((len + 1) * sizeof(char));
	if (!sdup)
		return (NULL);
	for (i = 0; s && s[i]; i++)
		sdup[i] = s[i];
	sdup[i] = '\0';

	return (sdup);
}
