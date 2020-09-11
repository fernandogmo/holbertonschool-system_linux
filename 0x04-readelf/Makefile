CC 	= 	$(if $(filter "$(USER)", "fernando"),gcc-4.9,gcc-4.8)
CFLAGS 	= 	-Wall -Werror -Wextra -pedantic -ggdb3
LINTER  =	betty

IDIR 	= 	./include
SDIR 	= 	./src
ODIR 	= 	./build

TGT0	= 	0-hreadelf
SRCS0 	= 	0-hreadelf.c \
		utils/print_elf_header.c \
		utils/print_magic.c \
		utils/print_class.c \
		utils/print_data.c \
		utils/print_version.c \
		utils/print_osabi.c \
		utils/print_abi_version.c \
		utils/print_type.c \
		utils/print_machine.c \
		utils/print_e_version.c \
		utils/print_machine.c \
		utils/print_entry.c \
		utils/print_start_program_headers.c \
		utils/print_start_section_headers.c \
		utils/print_flags.c \
		utils/print_elf_header_size.c\
		utils/print_section_header_names_index.c \
		utils/print_number_section_headers.c \
		utils/print_section_header_table_size.c \
		utils/print_number_program_headers.c \
		utils/print_program_header_table_size.c
		# utils/print_program_headers.c\
		# $(COMMON)

TGT1	=	1-hreadelf
SRCS1	=	1-hreadelf.c \
		utils/print_section_headers.c

# COMMON	=	$(wildcard /utils/*.c)

ALL_TGT	=	$(TGT0) $(TGT1)
ALL_SRC =	$(SRCS0) $(SRCS1)

OBJS0	= 	$(SRCS0:%.c=$(ODIR)/%.o)
OBJS1	= 	$(SRCS1:%.c=$(ODIR)/%.o)

DEPS	=	$(wildcard $(IDIR)/*.h)

$(ODIR)/%.o : $(SDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(IDIR)

all : $(ALL_TGT)

$(TGT0) : $(OBJS0)
	$(CC) -o $@ $^

$(TGT1) : $(OBJS1)
	$(CC) -o $@ $^

.PHONY : clean, re, lint, fullgrind
clean :
	rm -f $(foreach tgt, $(ALL_TGT), ./$(tgt))
	rm -rf $(ODIR)

re : clean all

lint :
	@$(LINTER) $(DEPS) $(foreach src, $(ALL_SRC), $(SDIR)/$(src))

# make fullgrind PROG=0-readelf ARGS="bin1 bin2"
fullgrind : clean $(PROG)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROG) $(shell echo $(ARGS))