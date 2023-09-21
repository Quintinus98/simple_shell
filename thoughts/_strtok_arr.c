/*
	parse tokens without allocating buffers and copying strings
	For the parsing used here, you can use strtok() to accomplish
	the same thing. For other types of parsing, strtok() may
	not be sufficient.

	Paul Krzyzanowski
*/

#include <stdio.h> 
#include <string.h>
#define MAXTOKENS 256

int
main(int argc, char **argv)
{
	char *grid[] = {"abc", "cd", ";", "efg", ";", "akse", "ald", NULL};	/* test string */
	char *item[MAXTOKENS];	/* this holds our array of tokens */
	char separator = ';';
	char *s;	/* where we're scanning */
	int i=0;	/* current item */
	

	item[i] = grid[0];	/* first token */
	for (; *grid; *grid = *grid + 1) {
		if (strcmp(*grid, separator) == 0) {		/* end of item */
			*grid = NULL;		/* mark end of string */
			while (strcmp(*grid + 1, separator) == 0) *grid = *grid + 1;	/* skip all separators */
			item[++i] = *grid + 1;
		}
	}

	/* print our list of tokens */
	int j;
	for (j=0; j <= i; j++) 
		printf("item %d: \"%s\"\n", j, item[j]);
}