#ifndef READELF_H
#define READELF_H 1

#include <elf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_ARGS 10
#define LABEL "  %-35s"
#define ERRX(fmt, filename) (errx(EXIT_FAILURE, "Error: " fmt, filename))

#define E_SET_ENDIAN(x) /* enclosed in do-while for `betty` style checker */ \
	do {\
	uint8_t  data = e->e64.e_ident[EI_DATA];\
	uint8_t class = e->e64.e_ident[EI_CLASS];\
	if (data == ELFDATA2MSB)\
		x = (class == ELFCLASS32) ? be32toh(e->e32.e_ ## x) :\
		    (class == ELFCLASS64) ? be64toh(x) : x;\
	else if (data == ELFDATA2LSB)\
		x = (class == ELFCLASS32) ? le32toh(e->e32.e_ ## x) :\
		    (class == ELFCLASS64) ? le64toh(x) : x;\
	} while (0)

#define S_SET_ENDIAN(x) /* enclosed in do-while for `betty` style checker */ \
	do {\
	uint8_t  data = e->e64.e_ident[EI_DATA];\
	uint8_t class = e->e64.e_ident[EI_CLASS];\
	if (data == ELFDATA2MSB)\
		x = (class == ELFCLASS32) ? be32toh(x) :\
		    (class == ELFCLASS64) ? be64toh(x) : x;\
	else if (data == ELFDATA2LSB)\
		x = (class == ELFCLASS32) ? le32toh(x) :\
		    (class == ELFCLASS64) ? le64toh(x) : x;\
	} while (0)

#define P_SET_ENDIAN(x) /* enclosed in do-while for `betty` style checker */ \
	do {\
	uint8_t  data = e->e64.e_ident[EI_DATA];\
	uint8_t class = e->e64.e_ident[EI_CLASS];\
	if (data == ELFDATA2MSB)\
		x = (class == ELFCLASS32) ? be32toh(p->p32.p_ ## x) :\
		    (class == ELFCLASS64) ? be64toh(x) : x;\
	else if (data == ELFDATA2LSB)\
		x = (class == ELFCLASS32) ? le32toh(p->p32.p_ ## x) :\
		    (class == ELFCLASS64) ? le64toh(x) : x;\
	} while (0)


/**
 * union ElfN_Ehdr - holds N-bit Elf file header type
 * @e32: for reading it as 32-bit arch
 * @e64: for reading it as 64-bit arch
 */
typedef union ElfN_Ehdr
{
	Elf32_Ehdr e32;
	Elf64_Ehdr e64;
} ehdr_t;

/**
 * union ElfN_Shdr - holds N-bit Elf section header type
 * @s32: for reading it as 32-bit arch
 * @s64: for reading it as 64-bit arch
 */
typedef union ElfN_Shdr
{
	Elf32_Shdr s32;
	Elf64_Shdr s64;
} shdr_t;

/**
 * union ElfN_Phdr - holds N-bit Elf program header type
 * @p32: for reading it as 32-bit arch
 * @p64: for reading it as 64-bit arch
 */
typedef union ElfN_Phdr
{
	Elf32_Phdr p32;
	Elf64_Phdr p64;
} phdr_t;

/* file header printing functions */
int print_elf_header(ehdr_t *);
int print_magic(Elf64_Ehdr *);
int print_class(Elf64_Ehdr *);
int print_data(Elf64_Ehdr *);
int print_version(Elf64_Ehdr *);
int print_osabi(Elf64_Ehdr *);
int print_osabi_more(Elf64_Ehdr *);
int print_abi_version(Elf64_Ehdr *);
int print_type(Elf64_Ehdr *);
int print_machine(Elf64_Ehdr *);
int print_e_version(ehdr_t *);
int print_entry(ehdr_t *);
int print_start_program_headers(ehdr_t *);
int print_start_section_headers(ehdr_t *);
int print_flags(ehdr_t *);
int print_elf_header_size(ehdr_t *);
int print_program_header_table_size(ehdr_t *);
int print_number_program_headers(ehdr_t *);
int print_section_header_table_size(ehdr_t *);
int print_number_section_headers(ehdr_t *);
int print_section_header_names_index(ehdr_t *);

/* section header printing functions */
int read_section_headers(shdr_t *, ehdr_t *, FILE *);
int print_section_headers(shdr_t *, ehdr_t *);

#endif /* READELF_H */
