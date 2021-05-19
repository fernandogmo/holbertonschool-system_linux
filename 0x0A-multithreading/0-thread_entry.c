#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/**
 * thread_entry - takes a string and prints it with new line
 * @arg: generic pointer
 * Return: generic pointer
 */
void *thread_entry (void *arg)
{
	if (arg) printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
