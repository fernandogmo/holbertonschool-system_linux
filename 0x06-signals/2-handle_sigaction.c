#include "signals.h"

/**
 * sigint_handler - action to take on SIGINT delivery
 * @signum: signal value to print
 */
static inline void sigint_handler(int signum __attribute__((__unused__)))
{
	#define SIGNUM EXPAND_AND_STRINGIFY(SIGINT)
	#define MSG "Gotcha! [" SIGNUM "]\n"
	signum = write(STDOUT_FILENO, MSG, sizeof(MSG) - 1);
}

/**
 * handle_sigaction - Sets a handler for SIGINT
 * Return: 1 on success, -1 on error
 */
int handle_sigaction(void)
{
	C99(
	struct sigaction act = {.sa_handler = sigint_handler};

	return (sigaction(SIGINT, &act, NULL));
	);
}
