#include "main.h"

/**
 * is_sep - checks if character matches seperator;
 * @ch: character
 * @sep: seperator
 * Return: 1 if it matches 0 if it doesnt.
*/
int is_sep(char ch, char *sep)
{
	while (*sep != '\0')
	{
		if (ch == *sep)
			return (1);
		sep++;
	}
	return (0);
}

/**
 * _strtok - tokenizes a string.
 * @str: string to tokenize.
 * @sep: seperator.
 * Return: Token or Null.
*/
char *_strtok(char *str, char *sep)
{
	static char *str_ptr;
	char *ret;

	if (!str)
		str = str_ptr;
	if (!str)
		return (NULL);

	while (1)
	{
		if (is_sep(*str, sep))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}

	ret = str;
	while (1)
	{
		if (*str == '\0')
		{
			str_ptr = str;
			return (ret);
		}
		if (is_sep(*str, sep))
		{
			*str = '\0';
			str_ptr = str + 1;
			return (ret);
		}
		str++;
	}
}
