CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -pedantic -ggdb3
LINTER	= betty

BASEDIR	= ./testing

SRCS_NM	= $(shell find $(BASEDIR)/nm -name "*.c")
IDIR_NM	= $(BASEDIR)/nm
# SRCS	= $(shell find . -path ./testing -prune -false -o -name "*.c")
# IDIR	= ./
SRCS_OD	= $(shell find $(BASEDIR)/objdump -name "*.c")
IDIR_OD	= $(BASEDIR)/objdump

OBJS_NM	= $(SRCS_NM:./%.c=./build/%.o)
OBJS_OD	= $(SRCS_OD:./%.c=./build/%.o)

# DEPS	= $(shell find $(BASEDIR) -name "*.h")

hnm: $(OBJS_NM)
	@$(CC) $(CFLAGS) -o $@ $(OBJS_NM) -I$(IDIR_NM)

hobjdump: $(OBJS_OD)
	@$(CC) $(CFLAGS) -o $@ $(OBJS_OD) -I$(IDIR_OD)

./build/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean lint
clean:
	@rm -rf $(OBJS_NM) $(OBJS_OD) ./hnm ./hobjdump
	@rm -rf ./build

lint :
	@$(LINTER) $(shell find $(BASEDIR) -name '*.h' -or -name '*.c')
