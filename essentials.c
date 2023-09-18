#include "main.h"

/**
 * prompt - Displays "$ {User input}";
 * @mode: Determines if the $ sign will be printed.
 * @line: Address of line in main.
 * Return: Returns the entered user input.
*/

void prompt(int mode, char **line)
{
	size_t linecap = 0;
	ssize_t linelen;

	if (mode == 1)
		write(1, "$ ", 2);
	linelen = _getline(line, &linecap, stdin);
	if (linelen == -1)
	{
		exit(errno);
	}
}


/**
 * string_to_array - splits string
 * @s: array of string character.
 * @sep: seperator.
 * Return: an array of each word of the string.
*/
char **string_to_array(char *s, char *sep)
{
	int i = 0, j = 0, elem = 0;
	char **arr = NULL, *token = NULL, *ptr = NULL, *ptr_cpy, ch;

	arr = malloc(30 * sizeof(char *));
	token = strtok(s, sep);
	for (i = 0; token != NULL; token = strtok(NULL, sep), i++)
	{
		ptr = token;
		if (update_arr_tok(arr, token, i) == 1)
			continue;
		ptr_cpy = ptr;
		for (j = 0; *ptr; j++, ptr++)
		{
			ch = check_ptr(*ptr, *(ptr + 1));
			if (ch != '0' && j == 0)
			{
				*(ptr + 1) = '\0';
				ptr += 2;
				ptr_cpy = ptr;
				update_arr(arr, ch, i);
				i++;
			}
			else if (ch != '0'  && j > 0 && elem == 1)
			{
				*ptr = '\0';
				arr[i] = ptr_cpy;
				ptr_cpy = ptr + 2;
				update_arr(arr, ch, i + 1);
				ptr = ptr_cpy;
				elem = 0;
				i += 2;
			}
			else
				elem = 1;
		}
		arr[i] = ptr_cpy;
	}
	arr[i] = NULL;
	return (arr);
}

/**
 * update_arr_tok - Updates the array with the token
 * @arr: array
 * @token: token
 * @i: index
 * Return: 1 if updated, 0 if not.
*/
int update_arr_tok(char **arr, char *token, int i)
{
	if (!strcmp(token, "||") || !strcmp(token, "&&"))
	{
		arr[i] = token;
		return (1);
	}
	return (0);
}

/**
 * update_arr - Updates the array with the string of char
 * @arr: array
 * @ch: character
 * @i: index
*/
void update_arr(char **arr, char ch, int i)
{
	if (ch == '|')
		arr[i] = "||";
	else
		arr[i] = "&&";
}

/**
 * check_ptr - Checks characters if they are equal
 * @ch: character ch
 * @sh: character sh
 * Return: character if matches | or & else return 0.
*/
char check_ptr(char ch, char sh)
{
	if (ch == sh)
	{
		if (ch == '|')
			return ('|');
		if (ch == '&')
			return ('&');
	}
	return ('0');
}
