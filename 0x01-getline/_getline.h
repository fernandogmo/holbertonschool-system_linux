#ifndef _GETLINE_H_
#define _GETLINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE BUFSIZ

/**
 * struct filebuf_t - holds tracking info et al.
 * @buf: READ_SIZE char buffer
 * @bufp: pointer for @buf
 * @n: chars in @buf
 * @is_open: have we opened this file descriptor before?
 */
typedef struct filebuf_t
{
	char buf[READ_SIZE];
	char *bufp;
	int n;
	unsigned int is_open : 1;
} filebuf_t;

ssize_t _fgetchar(const int fd);
char *_getline(const int fd);

#endif /* _LAPS_H_ */
