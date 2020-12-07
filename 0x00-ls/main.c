#include "hls.h"

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
	char **args = _calloc(BUFSIZE, sizeof(args));
	file_t **files = malloc(sizeof(**files) * BUFSIZE);
	file_t **dirs = malloc(sizeof(**dirs) * BUFSIZE);

	/* populate dirs and set options */
	(void) argc;
	parse_args(argv + 1, args, &options);
	if (!args[0])
		parse_args(def, args, &options);
	if (!args[0])
		perror("fail"), exit(2);

	/* separate dirs and regfiles */
	separate_files(args, files, dirs, &file_count, &dir_count);

	/* print all files in current dir */
	_alphasort(files, file_count);
	#if DEBUG
	printf("file count = %d\n", (int)file_count);
	#endif /* DEBUG */
	print_files_in_current_dir(files, file_count, options);

	/* print every file in every dir */
	_alphasort(dirs, dir_count);
	if (dir_count > 1)
		puts("");
	print_files_in_dirs(dirs, dir_count, options);

	for (i = 0; i < file_count; ++i)
		free(files[i]);
	for (i = 0; i < dir_count; ++i)
		free(dirs[i]);
	free(files);
	free(dirs);
	free(args);

	return (0);
}
