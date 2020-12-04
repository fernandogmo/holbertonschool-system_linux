#ifndef HLS_H
#define HLS_H

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define SLICE(str, a, b) (str[b] = '\0', &str[a])

int create_fullpath(char **buf, const char *path, char *file);
int hls(const char *argv[]);

size_t _strlen(const char *);

#endif /* HLS_H */
