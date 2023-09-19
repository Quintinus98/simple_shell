#include "main.h"

/**
 * comments - Removes comments from execution
 * @buf: string buffer.
*/
void comments(char *buf)
{
	int i = 0;

	if (!buf)
		return;
	for (; buf[i] != '\0'; i++)
	{
		if (buf[i] == ' ' && buf[i + 1] == '#')
			buf[i + 1] = '\0';
		else if (buf[i] == '#' && buf[i + 1] == '\0')
			buf[i] = '\0';
		else if (buf[i] == '#' && i == 0)
		{
			buf[i] = '\0';
			break;
		}
	}
}
