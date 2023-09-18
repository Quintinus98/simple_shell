#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct arraysub
{
	char **subarr;
	char *logOp;
	int pos;
} arraysub_t;

#define MAX_ELEM 10
arraysub_t getSubArray(char **arr, int i);
void freeSubArray(arraysub_t subArr);

int main(void)
{
	char *input[] = {"ls", "/var", "&&", "ls", "/var", "&&", "ls", "/hbtn", "&&", "ls", "/hbtn", "uu", NULL};
	arraysub_t subgrid;
	int i = 0, pos;

	subgrid = getSubArray(input, 0);
	while (subgrid.subarr)
	{
		for (i = 0; subgrid.subarr[i]; i++)
			printf("%s ", subgrid.subarr[i]);

		pos = subgrid.pos;
		freeSubArray(subgrid);
		subgrid = getSubArray(input, pos);
	}

	return (0);
}

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
	while (strcmp(arr[i], "&&") && strcmp(arr[i], "||"))
	{
		ret.subarr[j] = strdup(arr[i]);
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