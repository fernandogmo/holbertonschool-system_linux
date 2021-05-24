#include <stdio.h>
#include <pthread.h>
#include "multithreading.h"

pthread_mutex_t lock;

/**
  * construct_mutex - builds mutex before main function runs using a
  * *		      GCC constructor attribute
  */
__attribute__((constructor))void construct_mutex(void)
{
	pthread_mutex_init(&lock, NULL);
}

/**
  * destroy_mutex - builds mutex before main function runs using a
  * *		      GCC constructor attribute
  */
__attribute__((destructor))void destroy_mutex(void)
{
	pthread_mutex_destroy(&lock);
}


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
