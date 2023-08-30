#include "main.h"

/**
 * ilen - get length.
 * @n: number
 * Return: returns the length of a integer.
*/
int ilen(int n)
{
	unsigned int cnt = 0;

	while (n != 0)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt);
}
