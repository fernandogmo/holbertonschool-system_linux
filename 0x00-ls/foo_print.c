#include "hls.h"


void separate_files(char **args,
		    file_t **files, file_t **dirs,
		    size_t *file_count, size_t *dir_count)
{
	size_t i = 0;

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


void print_files_in_current_dir(file_t **files,
				size_t file_count,
				option_t options)
{
	char *buf = malloc(sizeof(*buf) * BUFSIZE);
	char *start = buf;
	size_t i = 0;

	/* TODO consider options */
	for (; i < file_count; ++i)
	{
		file_t *f = files[i];
		/* TODO consider options */
		char *sep = (options & ONEPERLINE) ? "\n" : "  ";

		buf += sprintf(buf, "%s%s", f->path, sep);
	}
	if (buf != start)
		_puts(start);
	free(start);
}


void read_subentries(DIR *dirp,
		     file_t *dom,
		     size_t *sub_count)
{
	struct dirent *d;

	while ((d = readdir(dirp)) != NULL)
	{
		file_t *sub = malloc(sizeof(*sub));

		sub->path = d->d_name;
		lstat(sub->path, &sub->sb);
		sub->is_dir = S_ISDIR(sub->sb.st_mode);
		dom->subentries[(*sub_count)++] = sub;
	}
}


void print_subentries(file_t *dom,
		      size_t sub_count,
		      size_t dir_count,
		      option_t options)
{
	char *buf = malloc(sizeof(*buf) * BUFSIZE);
	char *start = buf;
	size_t i = 0;

	if (dir_count > 1)
		printf("%s:\n", dom->path);
	for (; i < sub_count; ++i)
	{
		/* TODO consider options */
		char *sep = (options & ONEPERLINE) ? "\n" : "  ";

		buf += sprintf(buf, "%s%s", dom->subentries[i]->path, sep);
	}
	if (buf != start)
		_puts(start);
	free(start);
}


void print_files_in_dirs(file_t **dirs,
			 size_t dir_count,
			 option_t options)
{
	size_t i = 0;

	for (; i < dir_count; ++i)
	{
		file_t *dom = dirs[i];
		size_t sub_count = 0;
		DIR *dir = opendir(dom->path);

		dom->subentries = malloc(sizeof(dom->subentries) * BUFSIZE);

		read_subentries(dir, dom, &sub_count);

		/* Sort subentries with alphasort */
		sort_subentries(dom->subentries, sub_count);

		/* print sorted subentries */
		print_subentries(dom, sub_count, (size_t)dir_count, options);

		if (i < (dir_count - 1))
			_puts("");

		{
			size_t j = 0;

			for (; j < sub_count; ++j)
				free(dom->subentries[j]);
			free(dom->subentries);
		}
		closedir(dir);
	}
}
