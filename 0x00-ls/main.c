#include "hls.h"

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		printf("Usage: hls [OPTION]... [FILE]...\n");
		exit(1);
	}
	else
	{
		DIR *dirp = opendir(argv[1]);
		struct dirent *entp;

		while ((entp = readdir(dirp)) != NULL)
		{
			struct stat statbuf;
			char *pathbuf = NULL;

			if (create_fullpath(pathbuf, argv[1], entp->d_name) != 0)
			{
				fprintf(stderr, "create_fullpath failed");
				exit(1);
			}

			if (lstat(pathbuf, &statbuf) != 0)
			{
				fprintf(stderr, "lstat failed");
				exit(1);
			}
			else
			{
				off_t size = statbuf.st_size;

				printf("%s %lu\n", entp->d_name, size);
			}
		}
		exit(0);
	}
	/* Should be unreachable */
	return (127);
}

int create_fullpath(char *buf, const char *path, char *file)
{
	size_t len_path = strlen(path);
	size_t len_file = strlen(file);
	size_t extra_chars = 2;
	char *fmt = "%s%s";

	if (path[len_path - 1] != '/')
	{
		extra_chars = 3;
		fmt = "%s/%s";
	}
	buf = malloc((len_path + len_file + extra_chars) * sizeof(char));
	if (buf == NULL)
		return (1);
	sprintf(buf, fmt, path, file);

	return (0);
}
