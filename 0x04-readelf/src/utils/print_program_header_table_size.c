#include "readelf.h"

/**
 * print_program_header_table_size - prints size of header table entry
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_program_header_table_size(ehdr_t *e)
{
	Elf64_Half phentsize = e->e64.e_phentsize;

	E_SET_ENDIAN(phentsize);
	printf(LABEL"%d (bytes)\n", "Size of program headers:", phentsize);
	return (0);
}
