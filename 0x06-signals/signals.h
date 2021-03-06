#ifndef SIGNALS_H
#define SIGNALS_H 1

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef __sighandler_t sighandler_t; /* void (*fn)(int) */
typedef struct sigaction sigaction_t;
/*
 * Should I instead include `#define _GNU_SOURCE`?
 * See: https://stackoverflow.com/q/5582211/9221785
 */

int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);
int pid_exist(pid_t pid);
void all_in_one(void);
int sigset_init(sigset_t *set, int *signals);
int signals_block(int *signals);
int signals_unblock(int *signals);
int handle_pending(void (*handler)(int));
void all_in_one(void);
int sigset_init(sigset_t *set, int *signals);
int signals_block(int *signals);
int signals_unblock(int *signals);
int handle_pending(void (*handler)(int));

#define STRINGIFY(expr) #expr
#define EXPAND_AND_STRINGIFY(expr) STRINGIFY(expr)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"
#define C99(...) \
do { \
_Pragma("GCC diagnostic push")\
_Pragma("GCC diagnostic ignored \"-Wpedantic\"")\
	__VA_ARGS__ \
_Pragma("GCC diagnostic pop")\
} while (0)
#pragma GCC diagnostic pop

#ifdef __GNUC__
#define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#define __maybe_unused __attribute__((__unused__))
#else
#define UNUSED(x) UNUSED_##x
#endif

#ifdef __GNUC__
#define UNUSED_FUNCTION(x) (__attribute__((__unused__)) UNUSED_##x)
#else
#define UNUSED_FUNCTION(x) UNUSED_##x
#endif

#endif /* SIGNALS_H */
