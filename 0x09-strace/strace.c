#include "strace.h"
#include <stdio.h>


/**
 * wait_for_syscall - continue and stop at the next
 * *		      entry to or return from a syscall
 * @tracee: pid_t of traced process
 * Return: termination signal of @tracee
 */
static int wait_for_syscall(pid_t tracee)
{
	int status;

	do {
		ptrace(PT_SYSCALL, tracee, NULL, NULL);
		waitpid(tracee, &status, 0);
	} while (!(WIFSTOPPED(status)
		 && (WSTOPSIG(status) & 0x80))
		 && !WIFEXITED(status));
	return (WTERMSIG(status));
}
/**
 * print_from_user - print register value from USER region of
 *		    tracee at specified index. Assumes unbuffered stdout.
 * @tracee: pid_t of traced process
 * @index: int index offset register in @tracee USER region
 * @option: int REG_OPT or SYS_OPT to print sysnum or syscall name
 */
void print_from_user(pid_t tracee, int index, int option)
{
	long sysnum = ptrace(PT_READ_U, tracee, 8 * index);

	switch (option)
	{
	case REG_OPT:
		printf("%li\n", sysnum);
		break;
	case SYS_OPT:
	case RET_OPT:
		printf("%s", syscalls_64_g[sysnum].name);
		break;
	default:
		fprintf(stderr, "bad option to print_from_user\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * ptrace_and_print_syscall - trace attached process and print
 * *			      its system call number
 * @tracee: pid_t of traced process
 * @option: int REG_OPT or SYS_OPT to print sysnum or syscall name
 * Return: termination signal of @tracee
 */
int ptrace_and_print_syscall(pid_t tracee, int option)
{
	int status;

	waitpid(tracee, &status, 0);
	ptrace(PT_SETOPTIONS, tracee, 0, PTRACE_O_TRACESYSGOOD);
	while (wait_for_syscall(tracee))
	{
		print_from_user(tracee, ORIG_RAX, option);
		if (!wait_for_syscall(tracee))
			break;
		if (option == SYS_OPT) putchar('\n');
		if (option == RET_OPT)
			printf(" = %#lx\n", ptrace(PT_READ_U, tracee, 8 * RAX));
	}
	if (option == SYS_OPT) putchar('\n');
	if (option == RET_OPT) printf(" = ?\n");
	return (WTERMSIG(status));
}
