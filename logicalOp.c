#include "main.h"

/**
 * getSubArray - Gets sub array
 * @arr: array
 * @i: index
 * Return: A struct type of sub array.
*/
arraysub_t getSubArray(char **arr, int i)
{
	arraysub_t ret;
	int j = 0;

	if (arr[i] == NULL)
	{
		ret.subarr = NULL;
		ret.logOp = NULL;
		ret.pos = 0;
		return (ret);
	}
	if (i > 0)
		i++;
	ret.subarr = malloc(MAX_ELEM * sizeof(char *));
	while (_strcmp(arr[i], "&&") && _strcmp(arr[i], "||"))
	{
		ret.subarr[j] = _strdup(arr[i]);
		i++;
		j++;
		if (arr[i] == NULL)
			break;
	}
	ret.subarr[j] = NULL;
	ret.pos = i;
	if (arr[i])
		ret.logOp = arr[i];
	else
		ret.logOp = NULL;

	return (ret);
}

/**
 * string_to_arr - splits string
 * @s: array of string character.
 * @sep: seperator.
 * Return: an array of each word of the string.
*/
char **string_to_arr(char *s, char *sep)
{
	int i = 0;
	char **arr, *token;

	/** Create Dynamic array */
	arr = malloc(30 * sizeof(char *));
	if (arr == NULL)
		return (NULL);

	/** Get Token and use for loop to extract the rest. */
	token = _strtok(s, sep);
	while (token != NULL)
	{
		arr[i] = token;
		token = _strtok(NULL, sep);
		i++;
	}
	arr[i] = NULL;

	return (arr);
}

