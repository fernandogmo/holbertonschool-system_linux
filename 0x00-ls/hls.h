#ifndef HLS_H
#define HLS_H

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define BUFSIZE 1024
#define SLICE(str, a, b) (str[b] = '\0', &str[a])

/* bitflag type for storing option flags */
typedef unsigned char option_t;

/* Possible values for our option flags option_t */
#define NONE		(0)
#define ONEPERLINE	(1)
#define ALL		(1 << 1)
#define ALMOSTALL	(1 << 2)
#define HUMAN		(1 << 3)
#define LISTING		(1 << 4)

/**
 * struct file_node_t - (TODO) node on array backed doubly-linked list
 * @filename: name of file
 * @prev: index of previous node
 * @next: index of next node
 */
struct file_node_t
{
	char filename[256];

	size_t prev;
	size_t next;
};

/**
 * struct file_t - struct for file information
 * @path: full path name
 * @statbuf: contains lstat struct for file
 * @is_dir: boolean to cache whether file is directory
 * * `S_ISDIR(file->statbuf.st_mode)`
 * @subentries: pointer to array of subentries when file is directory
 */
typedef struct file_t
{
	char *path;
	struct stat statbuf;
	int is_dir;
	struct file_t **subentries;
} file_t;

/* main.c */
int create_fullpath(char **, const char *, char *);
int hls(const char *[]);

/* parse.c */
void parse_args(char **, char **, option_t *);
void parse_opts(char *, option_t *);

/* print.c */
void separate_files(char **, file_t **, file_t **, size_t *, size_t *);
void print_files_in_current_dir(file_t **, size_t, option_t);
void read_subentries(DIR *, file_t *, size_t *);
void print_subentries(file_t *, size_t, size_t, option_t);
void print_files_in_dirs(file_t **, size_t, option_t);

/* sort.c */
void _quicksort(file_t **, size_t);
void _alphasort(file_t **, int);
void sort_subentries(file_t **, int);

/* string.c */
size_t _strlen(const char *);
int _strcmp(char *, char *);
int _strcoll(char *, char *);

/* mem.c */
void *_memset(void *s, int c, size_t n);
void *_calloc(unsigned int nmemb, unsigned int size);

#endif /* HLS_H */
