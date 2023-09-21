#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct sep
{
	int val;
	char sepp;
} sep_t;
typedef struct tok
{
	char *token;
	char sep;
} tok_t;
char **string_to_array(char *s, char *sep);
int store_token(char **arr, char *token, int i);
tok_t _strtok(char *str, char *sep);
sep_t is_sep(char ch, char *sep);

int main (void)
{
	char input[] = "/bin/ks hbtnFTW&&/bin/ls || /bin/ls";
	char **grid;
	int i = 0;

	grid = string_to_array(input, "|& \n");
	while (grid[i])
	{
		printf("%s\n", grid[i]);
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
	int i = 0;
	char **arr;
	tok_t token;

	/** Create Dynamic array */
	arr = malloc(30 * sizeof(char *));
	if (arr == NULL)
		return (NULL);

	/** Get Token and use for loop to extract the rest. */
	token = _strtok(s, sep);
	while (token.token != NULL)
	{
		// i = store_token(&arr, token, i);
		arr[i] = token.token;
		if (token.sep == '|')
			arr[i = i + 1] = "||";
		else if (token.sep == '&')
			arr[i = i + 1] = "&&";		
		token = _strtok(NULL, sep);
		i++;
	}
	arr[i] = NULL;

	return (arr);
}


/**
 * is_sep - checks if character matches seperator;
 * @ch: character
 * @sep: seperator
 * Return: 1 if it matches 0 if it doesnt.
*/
sep_t is_sep(char ch, char *sep)
{
	sep_t ret;

	while (*sep != '\0')
	{
		if (ch == *sep)
		{
			ret.sepp = ch;
			ret.val = 1;
			return (ret);
		}
		sep++;
	}
	ret.val = 0;
	ret.sepp = '\0';
	return (ret);
}



/**
 * _strtok - tokenizes a string.
 * @str: string to tokenize.
 * @sep: seperator.
 * Return: Token or Null.
*/
/**  "/bin/ks hbtnFTW&&/bin/ls || /bin/ls" */
tok_t _strtok(char *str, char *sep)
{
	static char *str_ptr;
	tok_t ret;
	char sepr, pepr;
	char *ptr;
	sep_t st;

	ret.token = NULL;
	ret.sep = '\0';
	if (!str)
		str = str_ptr;
	if (!str)
		return (ret);

	while (1)
	{
		st = is_sep(*str, sep);
		if ((st.val && st.sepp == '|') || (st.val && (st.sepp == '|') && (is_sep(*(str + 1), sep).sepp == '|')))
		{
			ret.sep = '|';
			return (ret);
		}
		
		if (is_sep(*str, sep).val)
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (ret);
		break;
	}

	ret.token = str;
	while (1)
	{
		if (*str == '\0')
		{
			str_ptr = str;
			return (ret);
		}
		if (is_sep(*str, sep).val)
		{
			ret.sep = is_sep(*str, sep).sepp;
			*str = '\0';
			str_ptr = str + 1;
			return (ret);
		}
		str++;
	}
}
