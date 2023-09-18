#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char **string_to_array(char *s, char *sep);
char *_strdup(char *s);
void free_grid(char **grid);
char check_ptr(char ch, char sh);
void update_arr(char **arr, char ch, int i);
int update_arr_tok (char **arr, char *token, int i);

int main (void)
{
	char input[] = "ls /var || ls /var||&ls";
	char **grid;
	int i = 0;

	grid = string_to_array(input, " \n");
	while (grid[i])
	{
		printf("%d: %s\n", i, grid[i]);
		i++;
	}
	free(grid);
	return (0);
}

/**
 * string_to_array - splits string
 * @s: array of string character.
 * @sep: seperator.
 * Return: an array of each word of the string.
*/
char **string_to_array(char *s, char *sep)
{
	int i = 0, j = 0, k = 0, elem = 0;
	char **arr = NULL, *token = NULL, *ptr = NULL, *ptr_cpy, ch;

	if ((arr = malloc(30 * sizeof(char *))) == NULL)
		return (NULL);
	token = strtok(s, sep);
	for (i = 0; token != NULL; token = strtok(NULL, sep), i++)
	{
		ptr = token;
		if (update_arr_tok(arr, token, i) == 1)
			continue;
		ptr_cpy = ptr;
		for (j = 0; *ptr; j++, ptr++)
		{
			if ((ch = check_ptr(*ptr, *(ptr + 1))) != '0' && j == 0)
			{
				*(ptr + 1) = '\0';
				ptr += 2;
				ptr_cpy = ptr;
				update_arr(arr, ch, i);
				i++;
			}
			else if ((ch = check_ptr(*ptr, *(ptr + 1))) != '0'  && j > 0 && elem == 1)
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

int update_arr_tok (char **arr, char *token, int i)
{
	if (!strcmp(token, "||") || !strcmp(token, "&&"))
	{
		arr[i] = token;
		return (1);
	}
	return (0);
}
void update_arr(char **arr, char ch, int i)
{
	if (ch == '|')
		arr[i] = "||";
	else
		arr[i] = "&&";
}

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

/**
 * _strdup - Duplicates a string.
 * @s: string
 * Return: A duplicate of string s.
*/
char *_strdup(char *s)
{
	int i = 0, len = strlen(s);
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

/**
 * free_grid - prints a grid of integers
 * @grid: grid
 *
 * Return: Nothing.
 */
void free_grid(char **grid)
{
	int h;

	for (h = 0; grid[h] != NULL; h++)
	{
		free(grid[h]);
	}
	free(grid);
}
