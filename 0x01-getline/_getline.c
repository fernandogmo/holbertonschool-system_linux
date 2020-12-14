#include "_getline.h"
#include <string.h>

#define OPEN_MAX 255
static filebuf_t fds[OPEN_MAX];

/**
 * _fgetchar - get char from a file descriptor
 * @fd: int file descriptor to get chars from
 * Return: value of char read or -1 on EOF
 */
ssize_t _fgetchar(const int fd)
{
	filebuf_t *fb;
	int i;

	/* On fd == -1, zero out all filebufs in file descriptor array */
	if (fd == -1)
	{
		/* skip 0, 1, 2 for stdin, stdout, stderr */
		for (i = 3; i < OPEN_MAX; ++i)
		{
			/* if filebuf represents an open file, zero it out */
			fb = &fds[i];
			if (fb->been_opened)
			{
				dbg_printf(BLUE "%d had been opened. zeroing out now..\n" RESET, i);
				memset(fb, 0, sizeof(*fb));
				dbg_printf(RED "buf contents: %s\n" RESET, fb->buf);
			}
		}
		return (EOF);
	}

	/* use filebuf_t at index corresponding to fd */
	fb = &fds[fd];
	fb->been_opened = 1;
	if (fb->n == 0)
	{
		fb->n = read(fd, fb->buf, READ_SIZE);
		fb->bufp = fb->buf;
	}
	return ((--fb->n >= 0) ? (unsigned char)*(fb->bufp)++ : EOF);
}

/**
 * _getline - gets lines
 * @fd: int file descriptor to get lines from
 * Return: nul-terminated string (w/o the '\n' char)
 * *	or NULL on error or EOF
 */
char *_getline(const int fd)
{
	char *buf, *ptr;

	if (fd == -1)
	{
		_fgetchar(-1);
		return (NULL);
	}
	else
	{
		char c;

		buf = malloc(BUFSIZ);
		if (buf == NULL)
			return (NULL);
		ptr = buf;
		/* eptr = buf + BUFSIZ; */ /* TODO:  realloc if bigger buffer needed */
		/* fill buffer */
		while ((c = _fgetchar(fd)) >= 0)
		{
			*ptr++ = c;
			/* if newline, nul-terminate and return linebuffer*/
			if (c == '\n')
			{
				*(--ptr) = '\0';
				return (buf);
			}
		}
		/* if something was read, nul-terminate before returning */
		if (ptr - buf != 0)
			*ptr = '\0';
		else
		{
			free(buf);
			return (NULL);
		}
	}
	return (buf);
}
