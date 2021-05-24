#include <stdio.h>
#include <stdarg.h>
#include "multithreading.h"

static pthread_mutex_t lock;

/**
  * construct_mutex - builds mutex before main function runs using a
  * *		      GCC constructor attribute
  */
__attribute__((constructor))void construct_mutex(void)
{
	pthread_mutex_init(&lock, NULL);
}

/**
  * destroy_mutex - destroys mutex after main function runs using a
  * *		      GCC desstructor attribute
  */
__attribute__((destructor))void destroy_mutex(void)
{
	pthread_mutex_destroy(&lock);
}


/**
 * tprintf - takes a format string to print and prints it's thread id
 * @fmt: format string
 * Return: On success, positive int of characters printed, or negative on failure
 */
int tprintf(char const *fmt, ...)
{C99(
	va_list ap;
	va_start(ap, fmt);
	pthread_mutex_lock(&lock);
	int c = printf("[%lu] ", pthread_self());
	c += vprintf(fmt, ap);
	pthread_mutex_unlock(&lock);
	va_end(ap);
	return (c);
);}
