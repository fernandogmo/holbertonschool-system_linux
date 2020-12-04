#include "hls.h"

/**
 * create_type_rights - writes formatted type and permissions to char string
 * @buf: pointer to destination char buffer
 * @mode: latest modification time from struct timespec in struct stat
 * Return: number of chars written to buffer on success, negative on failure
 */
int create_type_rights(char **buf, mode_t mode)
{
	char type = S_ISREG(mode) ? '-' :
		    S_ISBLK(mode) ? 'b' :
		    S_ISCHR(mode) ? 'c' :
		    S_ISDIR(mode) ? 'd' :
		    S_ISLNK(mode) ? 'l' :
		    S_ISFIFO(mode) ? 'p' : '?';
	char rusr = mode & S_IRUSR ? 'r' : '-';
	char wusr = mode & S_IWUSR ? 'w' : '-';
	char xusr = mode & S_IXUSR ? 'x' : '-';
	char rgrp = mode & S_IRGRP ? 'r' : '-';
	char wgrp = mode & S_IWGRP ? 'w' : '-';
	char xgrp = mode & S_IXGRP ? 'x' : '-';
	char roth = mode & S_IROTH ? 'r' : '-';
	char woth = mode & S_IWOTH ? 'w' : '-';
	char xoth = mode & S_IXOTH ? 'x' : '-';

	return (sprintf(*buf, "%c%c%c%c%c%c%c%c%c%c",
		type, rusr, wusr, xusr, rgrp, wgrp, xgrp, roth, woth, xoth));
}

/**
 * create_time - writes formatted time to char string
 * @buf: pointer to destination char buffer
 * @timep: latest modification time from struct timespec in struct stat
 * Return: number of chars written to buffer on success, negative on failure
 */
int create_time(char **buf, time_t timep)
{
	char *time = ctime(&timep);
	size_t len = _strlen(time);

	*buf = malloc(len * sizeof(**buf));
	if (*buf == NULL)
		return (-1);
	return (sprintf(*buf, "%s", SLICE(time, 4, 16)));
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: pointer to array of strings
 * Return: 0 on success, non-zero code on failure
 */
int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		/* printf("Usage: hls [OPTION]... [FILE]...\n");
		exit(EXIT_FAILURE); */
		const char *cwd = ".";

		return (hls(&cwd));
	}

	return (hls(++argv));
}

/**
 * hls - process flags and list files 
 * @argv: pointer to array of strings
 * Return: 0 on success, non-zero code on failure
 */
int hls(const char *argv[])
{
	DIR *dirp = opendir(*argv);
	struct dirent *entp;

	while ((entp = readdir(dirp)) != NULL)
	{
		struct stat statbuf;
		char *pathbuf = NULL;

		if (create_fullpath(&pathbuf, *argv, entp->d_name) < 0)
		{
			fprintf(stderr, "create_fullpath failed\n");
			return (EXIT_FAILURE);
		}

		if (lstat(pathbuf, &statbuf) != 0)
		{
			perror("lstat");
			return (EXIT_FAILURE);
		}
		else
		{
			off_t size = statbuf.st_size;
			char *modebuf = malloc(10 * sizeof(*modebuf));
			char *timebuf = NULL;

			if (create_type_rights(&modebuf, statbuf.st_mode) < 0)
			{
				fprintf(stderr, "create_type_rights failed");
				return (EXIT_FAILURE);
			}
			if (create_time(&timebuf, statbuf.st_mtime) < 0)
			{
				fprintf(stderr, "create_time failed");
				return (EXIT_FAILURE);
			}
			printf("%s %ld %s %s\n", modebuf, size, timebuf, entp->d_name);
			free(modebuf);
			free(timebuf);
		}
		free(pathbuf);
	}
	closedir(dirp);
	return (0);
}

/**
 * create_fullpath - builds relative path string of file for use in lstat
 * @buf: pointer to destination char buffer
 * @path: string relative path of program call site
 * @file: string file name
 * Return: number of chars written to buffer on success, negative on failure
 */
int create_fullpath(char **buf, const char *path, char *file)
{
	size_t len_path = _strlen(path);
	size_t len_file = _strlen(file);
	size_t extra_chars = 2;
	char *fmt = "%s%s";

	if (path[len_path - 1] != '/')
	{
		extra_chars = 3;
		fmt = "%s/%s";
	}
	*buf = malloc((len_path + len_file + extra_chars) * sizeof(char));
	if (*buf == NULL)
		return (-1);
	return (sprintf(*buf, fmt, path, file));
}
