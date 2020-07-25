#include "../hls.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument array
 * Return: Returns success exit code
 */
int main(int argc, char **argv)
{
	char *def[] = {".", NULL};
	size_t i, file_count = 0, dir_count = 0;
	option_t options = NONE;
	char **args = malloc(sizeof(args) * BUFSIZE);
	file_t **files = malloc(sizeof(**files) * BUFSIZE);
	file_t **dirs = malloc(sizeof(**dirs) * BUFSIZE);

	/* populate dirs and set options */
	parse_args((char **)argv + 1, args, &options);

	/* separate dirs and regfiles */
	separate_files((argc == 1) ? def : args,
		       files, dirs, &file_count, &dir_count);

	/* print all files in current dir */
	_alphasort(files, file_count);
	print_files_in_current_dir(files, file_count);

	/* print every file in every dir */
	_alphasort(dirs, dir_count);
	if (dir_count > 1)
		puts("");
	print_files_in_dirs(dirs, dir_count);

	for (i = 0; i < file_count; ++i)
		free(files[i]);
	for (i = 0; i < dir_count; ++i)
		free(dirs[i]);
	free(files);
	free(dirs);
	free(args);

	return (0);
}
/**
 * parse_args - parses args
 * @args_in: input args
 * @args_out: output args
 * @options: bitflags
 */
void parse_args(char **args_in, char **args_out, option_t *options)
{
	char *arg = NULL;
	size_t i = 0;

	while ((arg = args_in[i]))
	{
		#if TESTING
		putchar(*arg), puts("");
		#endif
		if ((arg[0] == '-') && (arg[1] != '\0'))
		{
			parse_opts(arg, options);
		}
		else
		{
			args_out[i] = arg;
		}
		++i;
	}
	*options |= NONE;
}

/**
 * parse_opts - parses opts
 * @arg: arg containing option flag string
 * @options: options bitflag
 */
void parse_opts(char *arg, option_t *options)
{

	while (*++arg)
	{
		#if TESTING
		printf("%c\n", *arg);
		#endif
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
