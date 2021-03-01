#include "signals.h"

/**
 * sigquit_handler - action to take on SIGQUIT intercept
 * @sig: number of the signal that caused invocation of the handler
 * @info: pointer to a siginfo_t
 * @ucontext: pointer to a ucontext_t
 */
static inline void sigquit_handler(int sig, siginfo_t *info, void *ucontext)
{
	printf("SIGQUIT sent by %i\n", info->si_pid);
	fflush(stdout), (void)sig, (void)ucontext;
}

/**
 * trace_signal_sender - Defines a handler for SIGQUIT
 * Return: 0 on success, -1 on error
 */
int trace_signal_sender(void)
{C99(
	sigaction_t act = {
		.sa_sigaction = sigquit_handler,
		.sa_flags = SA_SIGINFO};

	return (sigaction(SIGQUIT, &act, NULL));
);
}
