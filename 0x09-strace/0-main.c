#include "strace.h"
#include <stdio.h>

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment vector
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *const argv[], char *const envp[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
		return (EXIT_FAILURE);
	}
	setbuf(stdout, NULL);
	pid_t pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0 && ptrace(PT_TRACE_ME) != -1)
	{
		kill(getpid(), SIGSTOP);
		return (execve(argv[1], argv + 1, envp));
	}
	ptrace_and_print_syscall(pid, REG_OPT);
	return (EXIT_SUCCESS);
}
