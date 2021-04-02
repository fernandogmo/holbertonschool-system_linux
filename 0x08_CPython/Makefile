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
	  -std=c99 \
	  -I/usr/include/python3.8 \
	  -fPIC \
	  -shared

.PHONY: 0 test clean again fullgrind check_version

all : foo bar
foo : CXXFLAGS += -DFOO
bar : CXXFLAGS += -DBAR
foo bar :
	@echo target=$@ CXXFLAGS=${CXXFLAGS}
.PHONY : all


1 : libPyList.so
libPyList.so: LDFLAGS = -Wl,-soname,PyList
libPyList.so: 1-python.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

2 3 : LDFLAGS = -Wl,-soname,libPython.so
2 3 :
	$(CC) $(CFLAGS) $(LDFLAGS) -o libPython.so $@-python.c

TARGET ?= 1
test: $(TARGET)
	timeout --signal=KILL 0.5s ./$<*.py

clean:
	$(RM) *.o *.so

again: clean 1

fullgrind: again
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./0.out

check_version:
	$(CC) --version
