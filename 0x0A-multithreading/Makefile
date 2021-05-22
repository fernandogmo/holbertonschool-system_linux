.PHONY: test bench fullgrind clean pycheck

% :
	@$(CC) $(CFLAGS) $(CEXTRAFLAGS) $(INCLUDE) -o $@.out $^ $(LDFLAGS) $(LDEXTRAFLAGS) $(LDLIBS)

0 : 0-main.c 0-thread_entry.c
1 : 1-main.c 1-tprintf.c
10: 10-main.c 10-blur_portion.c
10fake: 10-main.c 10-blur_portion.fakeimg.c
ARGS_10 := images/small_orig.pbm images/kernel_0.knl
11: 11-main.c 11-blur_image.c 10-blur_portion.c

TARGET ?= 10
TESTARGS ?= $(ARGS_10)
test: $(TARGET)
	@$(CC) --version | head -1 1> >(sed $$'s,.*,${BLUE}&${NC},' >&1)
	timeout --signal=KILL 2s ./$<.out $(TESTARGS)
	viu output.pbm

NUMTHREADS ?= 16
BENCHARGS ?= images/car_orig.pbm images/kernel_1.knl
bench: $(TARGET)
	time ./$<.out $(BENCHARGS)

clean:
	@$(RM) *.o *.so *.out

fullgrind: $(TARGET)
	@valgrind $(VALGRINDFLAGS) ./$<.out $(TESTARGS) \
	2> >(sed -e $$'/Invalid/s/.*/${RED}&${NC}/g' \
	         -e $$'s,.*,${GRAY}&${NC},' \
	         >&2)

lint:
	$(LINTER) *.c *.h

pycheck :
	@echo $(PYTHONLIB)

SHELL	:= bash
LINTER	:= betty

ifdef NIX_CC_FOR_TARGET
CC	:= $$NIX_CC_FOR_TARGET/bin/gcc
else
CC	:= gcc
endif

CFLAGS	+=	-std=c99
CFLAGS	+=	-ggdb3
CFLAGS	+=	-Wall
CFLAGS	+=	-Werror
CFLAGS	+=	-Wextra
CFLAGS	+=	-pedantic
# CFLAGS	+=	-fstack-protector-all # Add canary code to detect stack smashing
# CFLAGS	+=	-Wshadow # Warn when shadowing variables
# CFLAGS	+=	-O2 -D_FORTIFY_SOURCE=2 # Add canary code, i.e. detect buffer overflows
# CFLAGS	+=	-O3

INCLUDE	?=

LDFLAGS	?=
LDLIBS	+=	-lpthread

CEXTRAFLAGS	?= -DNUMTHREADS=$(NUMTHREADS)
LDEXTRAFLAGS	?=

VALGRINDFLAGS	+=	--leak-check=full
VALGRINDFLAGS	+=	--show-leak-kinds=all
VALGRINDFLAGS	+=	--track-origins=yes

# https://stackoverflow.com/a/33206814/9221785
RED	=	\e[31m
BLUE	=	\e[34m
NC	=	\e[0m
GRAY	= 	\e[90m
