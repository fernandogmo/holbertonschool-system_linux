#include <stddef.h>

/**
 * _strlen - takes a pointer to string and returns the length the string.
 * @src: pointer to a first char of string
 * Return: size_t length of input string
 */
size_t _strlen(const char *src)
{
	size_t len = 0;

	while (*src++)
		len++;
	return (len);
}
