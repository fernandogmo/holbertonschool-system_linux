#ifndef HNM_H
#define HNM_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void reverse(unsigned char *, size_t);
int read_elf_header_bytes(unsigned char *, const char *);
int check_elf(unsigned char *);
int read_bytes(unsigned char **, const char *, size_t, size_t);
uint16_t get_num_section_headers(unsigned char *, int, int);
void *get_section_header_off(unsigned char *, int, int);
Elf64_Off get_section_off(unsigned char *, int, int);
uint16_t get_section_hsize(unsigned char *, int, int);
uint64_t get_section_size(unsigned char *, int, int);

uint32_t get_sym_name_idx(unsigned char *, int, int);
Elf64_Addr get_sym_value(unsigned char *, int, int);
uint64_t get_sym_size(unsigned char *, int, int);
uint64_t get_section_es(unsigned char *, int, int);
int get_sh_idx_by_type(unsigned char *, int, int, uint32_t, short, short);
uint16_t get_sym_ndx(unsigned char *, int, int);
char get_sym_type_2(int, int, uint16_t);
uint32_t get_sh_type(unsigned char *, int, int);
uint64_t get_sh_flg(unsigned char *, int, int);
char get_sym_type_3(uint16_t, uint32_t, uint64_t);

#endif /* HNM_H */
