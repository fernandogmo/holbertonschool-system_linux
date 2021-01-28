#include "readelf.h"
#include <err.h>

static FILE *open_files[MAX_FILE_ARGS];

/**
 * exit_handler - frees memory from globals
 */
void exit_handler(void)
{
	int i = 0;

	for (; open_files[i]; ++i)
		fclose(open_files[i]);
}


/**
 * azrael - shepherds files into global cleanup array
 * @f: file to register into global array
 */
void azrael(FILE *f)
{
	static int i;

	open_files[i++] = f;
}

/**
 * main - prints elf file info like `readelf -hW`
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success else 1
 */
int main(int argc, char **argv)
{
	static ehdr_t e;
	FILE *f;
	int idx = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s elf-file", argv[0]);
		exit(EXIT_FAILURE);
	}
	atexit(&exit_handler);
	while (argv[++idx] && (f = fopen(argv[idx], "rb")))
	{
		azrael(f);
		fread(&e.e64, 1, sizeof(e), f);
		if (memcmp(e.e64.e_ident, ELFMAG, SELFMAG) == 0)
			print_elf_header(&e);
		else
			ERRX("%s: Failed to read file header", argv[idx]);
	}
	if (f == NULL && argv[idx])
		ERRX("'%s': No such file", argv[idx]);

	return (EXIT_SUCCESS);
}
