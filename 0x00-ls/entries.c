#include "hls.h"


/**
 * read_dirs - read DIR entries into dirent array and null-terminate
 * @dir: DIR file to read from
 * @entries: buffer for storing dirents
 * @options: readonly option bitflag
 * Return: Nothing
 */
void read_dirs(DIR *dir, struct dirent **entries, const option_t options)
{
	struct dirent *d = NULL;
	int i = 0;

	if (!dir)
	{
		#if TESTING
		#pragma message "Set appropriate errno"
		#endif /* TESTING */
		perror("Passed NULL dir to `read_dirs`");
		exit(1);
	}
	while ((d = readdir(dir)) != NULL)
	{
		if (!options && d->d_name[0] == '.')
			continue;
		entries[i++] = d;
	}
	entries[i] = NULL;

}

/**
 * print_dnames - prints d_name for each dirent in @entries array
 * @entries: NULL-terminated dirent array
 * @options: options bitflag
 * Return: Nothing
 */
void print_dnames(struct dirent **entries, const option_t options)
{
	struct dirent *d = NULL;
	char *buf = malloc(BUFSIZE);
	char *start = buf;

	while ((d = *(entries++)))
	{
		#if TESTING
		#pragma message "TODO: nest inside of listing check"
		#endif /* TESTING */
		char *sep = (options & ONEPERLINE) ? "\n" : "  ";

		buf += sprintf(buf, "%s%s", d->d_name, sep);
	}
	puts(start);
	free(start);
}

void print_dirs(struct file_t **files, size_t len, const option_t options)
{
	size_t i = 0;

	for (; i < len; ++i)
	{
		printf("%s:", files[i]->path);
		_puts((i < (len - 1)) ? "\n" : "");
	}
	(void)options;
}
