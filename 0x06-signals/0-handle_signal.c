#include "signals.h"

/**
 * sigint_handler - prints message with value of SIGINT when caught
 * @signum: int signal caught. unused due to optimizations.
 */
void sigint_handler(int signum __attribute__((__unused__)))
{
	/* we can compute the platform's `SIGINT` at compile-time :) */
	#define SIGNUM EXPAND_AND_STRINGIFY(SIGINT)
	/* `printf` is not async-signal-safe so we use `write` */
	write(STDOUT_FILENO, "Gotcha! [" SIGNUM "]\n", 13);
}

/**
 * handle_signal - sets a handler for the signal `SIGINT`
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	return (signal(SIGINT, sigint_handler) == SIG_ERR ? -1 : 0);
}
