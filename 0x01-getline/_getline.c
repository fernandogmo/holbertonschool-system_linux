#include "_getline.h"

/**
 * _fgetchar - get char from a file descriptor
 * @fd: int file descriptor to get chars from
 * Return: value of char read or -1 on EOF
 */
ssize_t _fgetchar(const int fd)
{
	static char buf[READ_SIZE];
	static char *bufp = buf;
	static int n;

	if (n == 0)
	{
		n = read(fd, buf, READ_SIZE);
		bufp = buf;
	}
	return ((--n >= 0) ? (unsigned char) *bufp++ : EOF);
}


/**
 * _getline - gets lines
 * @fd: int file descriptor to get lines from
 * Return: nul-terminated string (w/o the '\n' char)
 * *	or NULL on error or EOF
 */
char *_getline(const int fd)
{
	static char *buf;

	buf = malloc(BUFSIZ);
	if (buf == NULL)
		return (NULL);
	{
		char c;
		static char *ptr, *eptr;

		ptr = buf;
		eptr = buf + BUFSIZ;

		while ((c = _fgetchar(fd)) > 0)
		{
			*ptr++ = c;
			if (c == '\n')
			{
				*(--ptr) = '\0';
				return (buf);
			}
		}
		if (ptr - buf != 0)
			*ptr = '\0';
		else
		{
			free(buf);
			return (NULL);
		}

		(void)eptr; /* TODO:  realloc if bigger buffer needed */
	}

	return (buf);
}
