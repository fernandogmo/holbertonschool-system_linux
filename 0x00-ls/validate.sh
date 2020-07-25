#!/usr/bin/env bash
args='foo_sort.c lib foo_mem.c foo'
ls  $args "$@"
echo -e '\033[31m======================================================================================================================================\033[0m'
gcc-4.9 -Wall -Werror -Wextra -pedantic -g3 -fdiagnostics-color=always foo*.c -o hls && ./hls $args "$@"
