#include <stdlib.h>
#include <stdio.h>
#include "multithreading.h"


/**
* prime_factors - (SLOWLY) makes linked list of prime factors of an integer
* @s: char * number to be factorized
* Return: list_t with prime factors of @s, else NULL on failure
*/
list_t *prime_factors(char const *s)
{
	if (!s) return (NULL);
	size_t n = strtoul(s, NULL, 10), d = 2;
	list_t *primes = malloc(sizeof(*primes));
	if (!primes) return (NULL);
	list_init(primes);
	while (n > 1)
	{
		if (n % d) d++;
		else
		{
			size_t *p = malloc(sizeof(*p));
			if (p) *p = d; else return (NULL);
			printf("d = %lu, ", d);
			list_add(primes, p);
			n /= d;
		}
	}
	puts("");
	return (primes);
}
