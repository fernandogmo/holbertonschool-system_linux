#!/usr/bin/env bash
args='../main.c ../lib ../entries.c ../foo'
ls -a $args
echo -e '\033[31m======================================================================================================================================\033[0m'
gcc-4.9 -Wall -Werror -Wextra -pedantic -g3 -fdiagnostics-color=always foo*.c -o foo && ./foo $args
