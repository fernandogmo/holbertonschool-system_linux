#ifndef OBJDUMP_H
#define OBJDUMP_H

#include <elf.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>

#include "flags.h"

#define ALIGNMENT 16
#define GET_EHDR(cls, hdr, field) (cls == ELFCLASS32 ?				\
								   ((Elf32_Ehdr *)(hdr))->field		\
								   : ((Elf64_Ehdr *)(hdr))->field)

#define GET_SHDR(cls, hdr, field) (cls == ELFCLASS32 ?				\
								   ((Elf32_Shdr *)(hdr))->field		\
								   : ((Elf64_Shdr *)(hdr))->field)

#define CONVERT(data, field, cls, s1, s2)							\
	do {															\
		if (data == ELFDATA2MSB)										\
			reverse((uint8_t *)&(field), cls == ELFCLASS32 ? s1 : s2);	\
	} while (0)

/**
 * struct hdr_s - header struct
 * @addr: address of header
 * @entsize: entry size
 * @num: num of elements
*/
typedef struct hdr_s
{
	void *addr;
	uint16_t entsize;
	uint16_t num;
} hdr_t;

/**
 * struct elf_s - struct containing elf headers
 * @cls: 32 or 64 bit
 * @data: big or little endian
 * @ehdr: Elf header
 * @file: elf file
 * @file_size: file size
 * @shdr: section header
 * @phdr: program header
 */
typedef struct elf_s
{
	int cls;
	int data;
	void *ehdr;
	char *file;
	size_t file_size;
	hdr_t shdr;
	hdr_t phdr;
} elf_t;

void reverse(unsigned char *bytes, size_t size);
int check_elf(unsigned char *bytes);


void print_file_headers(elf_t *elf);
int get_flags(elf_t *elf);
int get_syms_flag(elf_t *elf);
void print_flags(int flags);
int skip_section(elf_t *elf, void *shdr);
int init_elf(elf_t *elf);
void objdump(elf_t *elf);
void print_sections(elf_t *elf, uint8_t *str_tab);
int get_width(uint64_t start, uint64_t size);
#endif /* OBJDUMP_H */
