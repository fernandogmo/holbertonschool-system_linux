# 0x00. C - ls
An `ls`-compatible binary for a legacy `Ubuntu 14.04` system with `gcc-4.8`
## Constraints
* Compilation:
    - `gcc-4.8 -Wall -Werror -Wextra -pedantic *.c -o hls` with no warnings or errors
* Execution:
    - Program will be run on an `Ubuntu 14.04` container via Holberton School's infrastructure 
* Allowed Functions and System Calls:
    - `opendir` (man 3 opendir)
    - `readdir` (man 3 readdir)
    - `closedir` (man 3 closedir)
    - `exit` (man 3 exit)
    - `free` (man 3 free)
    - `lstat` (man 2 lstat)
    - `malloc` (man 3 malloc)
    - `perror` (man 3 perror)
    - `write` (man 2 write)
    - `printf` (man 3 printf)
    - `sprintf` (man 3 sprintf)
    - `fprintf` (man 3 fprintf)
    - `readlink` (man 2 readlink)
    - `ctime` (man 3 ctime)
    - `getpwuid` (man 3 getpwuid)
    - `getgrgid` (man 3 getgrgid)
    - `errno` (man 3 errno)
## Questions
* What is a `directory stream`?
* 