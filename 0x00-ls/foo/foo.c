#include "../hls.h"


void separate_files(char **args,
	file_t **files, file_t **dirs,
	int *file_count, int *dir_count)
{
	int i = 0;

	for (; args[i]; ++i)
	{
		file_t *f = malloc(sizeof(*f));

		f->path = args[i];
		lstat(f->path, &f->sb);
		f->is_dir = S_ISDIR(f->sb.st_mode);
		if (!f->is_dir)
		{
			files[(*file_count)++] = f;
		}
		else
		{
			dirs[(*dir_count)++] = f;
		}
	}
}
void print_files_in_current_dir(file_t **files, int file_count)
{
	char *buf = malloc(sizeof(*buf) * BUFSIZE);
	char *start = buf;
	int i = 0;

	/* TODO consider options */

	for (; i < file_count; ++i)
	{
		file_t *f = files[i];

		buf += sprintf(buf, "%s  ", f->path);
	}
	if (buf != start)
		puts(start);
	free(start);
}
void print_files_in_dirs(file_t **dirs, int dir_count)
{
	int i = 0;

	for (; i < dir_count; ++i)
	{
		char *buf = malloc(sizeof(*buf) * BUFSIZE);
		char *start = buf;
		file_t *dom = dirs[i];
		size_t sub_count = 0;
		struct dirent *d;
		DIR *dir = opendir(dom->path);

		dom->subentries = malloc(sizeof(dom->subentries) * BUFSIZE);

		if (dir_count > 1)
			printf("%s:\n", dom->path);
		while ((d = readdir(dir)) != NULL)
		{
			/* TODO read entries into subentries */
			file_t *sub = malloc(sizeof(*sub));

			sub->path = d->d_name;
			lstat(sub->path, &sub->sb);
			sub->is_dir = S_ISDIR(sub->sb.st_mode);
			dom->subentries[sub_count++] = sub;
			/* buf += sprintf(buf, "%s  ", d->d_name); */
		}
		/* Sort subentries with alphasort */
		/* TODO this segfaults */
		_sort_subentries(dom->subentries, sub_count);
		printf("%lu\n", sub_count);

		/* TODO consider options */
		/* print sorted subentries */
		{
			size_t j = 0;
			for (; j < sub_count; ++j)
			{
				buf += sprintf(buf, "%s  ", dom->subentries[j]->path);
			}
		}

		if (buf != start)
			puts(start);
		free(start);
		if (i < (dir_count - 1))
			puts("");

		{
			size_t j = 0;
			for (; j < sub_count; ++j)
				free(dom->subentries[j]);
			free(dom->subentries);
		}
		closedir(dir);
	}
}
int main(int argc, char *argv[])
{
	file_t **files = malloc(sizeof(**files) * BUFSIZE);
	file_t **dirs  = malloc(sizeof(**dirs) * BUFSIZE);
 	char *def[] = {".", NULL};
	char **args = argv + 1;
	int i, file_count = 0, dir_count = 0;

	/* if (argc == 0)
	{
		file_t *f = malloc(sizeof(*f));

		f->path = ".";
		lstat(".", &f->sb);
		f->is_dir = TRUE;
		dirs[0] = f;
		print_files_in_dirs(dirs, (dir_count = 1));
		goto exit;
	} */

	/* separate dirs and regfiles */
	separate_files((argc == 1) ? def : argv + 1,
			files, dirs, &file_count, &dir_count);
	(void)args;


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

	return (0);
}
