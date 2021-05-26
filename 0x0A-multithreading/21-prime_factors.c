#include <stdlib.h>
#include <stdio.h>
#include "multithreading.h"


/**
* prime_factors - (SLOWLY) makes linked list of prime factors of an integer
* @s: char * number to be factorized
* Return: list_t with prime factors of @s, else NULL on failure
*/
list_t *prime_factors(char const *s)
{C99(
	list_t *ps = malloc(sizeof(*ps));
	if (!ps || !s) { free(NULL); return (NULL);}
	list_init(ps);
	size_t i = 0, a[64] = {0};
	size_t d = 2, n = strtoul(s, NULL, 10);
	while (n >= d*d)
	{
		if (n % d) d += (d % 2) + 1;
		else n /= (a[i++] = d);
	}
	for(a[i] = n, i = 0; a[i] > 1; i++)
	{
		size_t *p = malloc(sizeof(*p));
		if (p) *p = a[i]; else return (NULL);
		list_add(ps, p);
	}
	return (ps);
);}
