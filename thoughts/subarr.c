#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	// Pointer to first string in sub-array
	char **arr;
	// Number of strings in sub-array
	int count;
	char *logOp;
} string_array_t;

#define MAX_SUB_ARRAYS 10

int main (void)
{
	char *input[] = {"hello", "I", "am", "||", "a", "cool", "&&", "guy", NULL};
	string_array_t string_arrays[MAX_SUB_ARRAYS] = {0};
	string_array_t *cur = NULL;
	size_t n_arr = 1;
	int i = 0, j = 0, k = 0;
	char *logicalOp = NULL;

	// Pointer to current sub-array
	cur = &string_arrays[0];
	for (i = 0; input[i]; i++)
	{
		if (strcmp(input[i], "||") == 0 || strcmp(input[i], "&&") == 0) {
			// Store total number of strings in this sub-array
			cur->logOp = strdup(input[i]);
			cur->count = k;
			k = 0;
			// Switch to next sub-array
			cur = &string_arrays[++j];
			if (j >= MAX_SUB_ARRAYS) {
					fprintf(stderr, "Not enough sub-arrays allocated ...\n");
					break;
			}
			n_arr++;
			continue;
		}
		if (k == 0) {
			cur->arr = &input[i];
		}
		k++;
	}
	cur->count = k;
	cur->logOp = "nil";


	printf("Found %zu sub arrays ...\n", n_arr);
	for (i = 0; i < n_arr; i++) {
		string_array_t *cur = &string_arrays[i];
		for (j = 0; j < cur->count; j++)
		{
			printf("%s ", *(cur->arr++));
		}
		printf("%s\n", cur->logOp);
	}
}
