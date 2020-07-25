#include "../hls.h"

/**
 * _calloc - allocates memory for an array of nmemb elements of
 *	     size bytes each and returns a pointer to the
 *	     allocated memory.
 * @nmemb: integer number of elements desired in array
 * @size: integer number of bytes for each element
 * Return: pointer to resulting array, or NULL if malloc fails
 *	   or nmemb or size were set to zero.
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *ret;
	size_t bytes;

	bytes = nmemb * size;
	if (!bytes)
		return (NULL);

	ret = malloc(bytes);
	if (ret)
		return (_memset(ret, 0, bytes));

	return (NULL);
}


/**
 * _memset - fills the first n bytes of the memory area pointed
 *	     to by s with the constant byte c
 * @s: pointer to memory area
 * @c: byte to fill s with
 * @n: number of bytes to fill
 * Return: pointer to the memory area s.
 */
void *_memset(void *s, int c, size_t n)
{
	char *ptr = s;

	while (n--)
		*ptr++ = c;

	return (s);
}
