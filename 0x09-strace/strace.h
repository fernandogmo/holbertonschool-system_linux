#ifndef STRACE_H
#define STRACE_H

#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <signal.h>

#include "syscalls.h"

/* options for ptrace_and_print_syscall and print_from_user */
#define REG_OPT 0 /* print the long int sysnum for the syscall */
#define SYS_OPT 1 /* print the syscall name */
#define RET_OPT 2 /* print return value of the syscall */
int ptrace_and_print_syscall(pid_t tracee, int option);
void print_from_user(pid_t tracee, int index, int option);


#endif /* STRACE_H */
