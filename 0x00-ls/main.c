#include "hls.h"

void parse_args(char **argv, DIR **dirs, option_t *options)
{
	char *arg = NULL;

	while ((arg = *++argv))
	{
		putchar(*arg), puts("");
		if ((arg[0] == '-') && (arg[1] != '\0'))
		{
			parse_opts(arg, options);
		}
	}
	*options |= NONE;
	(void)dirs;
}

void parse_opts(char *arg, option_t *options)
{

	while (*++arg)
	{
		printf("%c\n", *arg);
		switch (*arg)
		{
		case '1':
			*options |= ONEPERLINE;
			#if TESTING
			puts("made it to case '1' in `parse_opts`");
			#endif
			break;

		case 'a':
			*options |= ALL;
			break;

		case 'A':
			*options |= ALMOSTALL;
			break;

		case 'h':
			*options |= HUMAN;
			break;

		case 'l':
			*options |= LISTING;
			break;

		default:
			#if TESTING
			#pragma message "TODO: handle bad flag"
			#endif /* TESTING */
			fprintf(stderr, "Unknown flag\n");
			exit(2);
			break;
		}
	}
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument array
 * Return: Returns success exit code
 */
int main(int argc, const char **argv)
{
	option_t options = NONE;
	DIR *dirs = malloc(BUFSIZE);
	struct dirent *entries[BUFSIZE];

	#if TESTING
	MARQUEE;
	#endif /* TESTING */

	/* populate dirs and set options */
	parse_args((char **)argv, &dirs, &options);

	if (argc == 1)
	{
		DIR *dir = opendir(".");

		read_dirs(dir, entries, options);
		print_dnames(entries, options);
		closedir(dir);
	}
	else
	{
		DIR *dir = NULL;

		read_dirs(dir, entries, options);
		print_dnames(entries, options);
		closedir(dir);
	}
	free(dirs);

	#if TESTING
	MARQUEE;
	#endif /* TESTING */

	return (0);
}
