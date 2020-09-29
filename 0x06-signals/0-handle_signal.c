#include "signals.h"

/**
 * sig_handler - prints message with value of signal caught
 * @signum: signal number caught by `signal`
 */
void sig_handler(int signum)
{
	/* not async-safe!!! */
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - sets a handler for the signal `SIGINT`
 * Return: 0 on success, -1 on error
 */
int handle_signal(void)
{
	return (signal(SIGINT, sig_handler) == SIG_ERR ? -1 : 0);
}
