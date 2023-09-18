#include "main.h"

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

void freeSubArray(arraysub_t subArr)
{
	int i = 0;

	while (subArr.subarr[i])
	{
		free(subArr.subarr[i]);
		i++;
	}
	free(subArr.subarr);
}