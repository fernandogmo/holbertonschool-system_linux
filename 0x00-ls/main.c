#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

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
            struct stat *buf = NULL;

            lstat(argv[1], buf);
            printf("%s\n", entp->d_name);
        }
        exit(0);
    }
    /* Should be unreachable */
    return 127;
}
