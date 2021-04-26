SHELL	= bash

ifdef NIX_CC_FOR_TARGET
CC	= $$NIX_CC_FOR_TARGET/bin/gcc
else
CC	= gcc
endif

CFLAGS	= -Wall \
	  -Werror \
	  -Wextra \
	  -pedantic \
	  -ggdb3 \
	  -std=c99

.PHONY: test clean again fullgrind check_version

% :
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@.out $^

ex_0 : ex_0.c
ex_1 : ex_1.c
ex_2 : ex_2.c
strace_0 : 0-main.c strace.c
strace_1 : 1-main.c strace.c
strace_2 : 2-main.c strace.c
strace_3 : 3-main.c strace.c
strace_4 : 4-main.c strace.c

RED = \033[0;31m
BLUE = \033[0;34m
NC  = \033[0m

TARGET ?= strace_2
test: $(TARGET)
	@echo -en "${BLUE}"
	@$(CC) --version | head -1
	@echo -en "${NC}"
	timeout --signal=KILL 0.5s ./$<.out /bin/echo Holberton | tee /dev/tty | wc

clean:
	@$(RM) *.o *.so

again: clean 5

fullgrind: again
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./0.out

gcc_version:
	$(CC) --version

pycheck :
	@echo $(PYTHONLIB)
