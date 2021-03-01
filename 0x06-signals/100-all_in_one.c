#include "signals.h"
/**
 * all_sig_handler - handler for all capturable signals
 */
//  * @sig: number of the signal that caused invocation of the handler
//  * @info: pointer to a siginfo_t
//  * @ucontext: pointer to a ucontext_t
#define ARGS int sig __maybe_unused,\
	     siginfo_t *info,\
	     void *ucontext __maybe_unused
static inline void all_sig_handler(ARGS)
{
	psiginfo(info, "Caught");
}

/**
 * all_in_one - Sets up a handler for all signals
 */
void all_in_one(void)
{
	int sig;
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = all_sig_handler;
	for (sig = 1; sig <= SIGRTMAX; ++sig)
		sigaction(sig, &act, NULL);
}
