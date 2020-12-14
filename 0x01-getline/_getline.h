#ifndef _GETLINE_H_
#define _GETLINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE BUFSIZ

#ifdef DEBUG
#define dbg_printf printf
#define RED		"\x1B[31m"
#define BLUE	"\x1B[34m"
#define RESET	"\033[0m"
#else
#define dbg_printf(...)
#endif /* DEBUG */

/**
 * struct filebuf_t - holds tracking info et al.
 * @buf: READ_SIZE char buffer
 * @bufp: pointer for @buf
 * @n: chars in @buf
 * @been_opened: have we opened this file descriptor before?
 */
typedef struct filebuf_t
{
	char buf[READ_SIZE];
	char *bufp;
	ssize_t n;
	unsigned int been_opened : 1;
} filebuf_t;

ssize_t _fgetchar(const int fd);
char *_getline(const int fd);

#endif /* _LAPS_H_ */
