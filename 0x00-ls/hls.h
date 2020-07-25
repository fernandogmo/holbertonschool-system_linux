#ifndef _HLS_H_
#define _HLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "holberton.h"

#define TESTING 0
#define ANSI_TERM_RED "\033[31m"
#define ANSI_TERM_RESET "\033[0m"
#define CHARS "===================================="
#define MARQUEE _puts(ANSI_TERM_RED CHARS CHARS ANSI_TERM_RESET)
#define SCREAM(msg) _puts(ANSI_TERM_RED msg ANSI_TERM_RESET)

#define BUFSIZE 1024
#define UNUSED(x) __attribute__((__unused__)) UNUSED_ ## x

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
	int is_dir;
	struct file_t **subentries;
} file_t;

void parse_args(char **, char **, option_t *);
void parse_opts(char *, option_t *);

void separate_files(char **, file_t **, file_t **, size_t *, size_t *);
void print_files_in_current_dir(file_t **, size_t, option_t);
void read_subentries(DIR *, file_t *, size_t *);
void print_subentries(file_t *, size_t, size_t, option_t);
void print_files_in_dirs(file_t **, size_t, option_t);

void _quicksort(file_t **, size_t);
void _alphasort(file_t **, int);
void sort_subentries(file_t **, int);

void dbg_print_array(file_t **, size_t);
void dbg_swap(file_t **, file_t **, file_t **, size_t);
void dbg_print_binary(unsigned char);

int _strcoll(char *, char *);
int _strcmp(char *, char *);


void *_memset(void *s, int c, size_t n);
void *_calloc(unsigned int nmemb, unsigned int size);


#endif /* _HLS_H_ */
