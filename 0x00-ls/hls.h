#ifndef _HLS_H_
#define _HLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "holberton.h"

#define TESTING 1
#define ANSI_TERM_RED "\033[31m"
#define TERMRESET "\033[0m"
#define CHARS "===================================="
#define MARQUEE puts(ANSI_TERM_RED CHARS CHARS TERMRESET)

#define BUFSIZE 1024
#define UNUSED(x) __attribute__((__unused__)) UNUSED_ ## x

/**
 * enum bool_t - homebrew boolean for ANSI C compliance
 * @FALSE: 0
 * @TRUE: 1
 */
typedef enum bool_t
{
	FALSE, TRUE
} bool_t;

typedef unsigned char option_t;

#define NONE        (0)
#define ONEPERLINE  (1)
#define ALL         (1 << 1)
#define ALMOSTALL   (1 << 2)
#define HUMAN       (1 << 3)
#define LISTING     (1 << 4)

/**
 * struct file_t - struct for file information
 * @path: full path name
 * @stat: contains lstat struct for file
 * @is_dir: boolean to cache whether file is directory
 * * `S_ISDIR(file->stat.st_mode)`
 * @subentries: pointer to array of subentries when file is directory
 */
typedef struct file_t
{
	char *path;
	struct stat sb;
	bool_t is_dir;
	struct file_t **subentries;
} file_t;

void parse_args(char**, DIR **, option_t *);
void parse_opts(char *, option_t *);
void print_dnames(struct dirent **, const option_t);
void read_dirs(DIR *, struct dirent **, const option_t);


void _quicksort(file_t **, size_t);
void _alphasort(file_t **, int);
void _sort_subentries(file_t **, int);


#endif /* _HLS_H_ */
