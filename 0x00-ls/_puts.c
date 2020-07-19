#include "holberton.h"

/**
 * _puts - takes a pointer to string and prints the string
 *         it's pointing to, followed by a newline.
 * @str: pointer to a char
 *
 */
void _puts(char *str)
{
	while (*str)
	{
		_putchar(*str);
		str++;
	}
	_putchar('\n');
}
