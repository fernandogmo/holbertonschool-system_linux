#include <stdio.h>
#include "multithreading.h"

/**
 * tprintf - takes a format string to print and prints it's thread id
 * @format: format string
 * Return: On success, positive int of characters printed, or negative on failure
 */
int tprintf(char const *format, ...)
{
	if (format)
		return (printf("[%lu] %s", pthread_self(), format));
	return (-1);
}
