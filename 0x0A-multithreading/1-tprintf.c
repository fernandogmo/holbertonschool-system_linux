#include <stdio.h>
#include "multithreading.h"

int tprintf(char const *format, ...)
{
	if (format)
		return (printf("[%lu] %s", pthread_self(), format));
	return (-1);
}
