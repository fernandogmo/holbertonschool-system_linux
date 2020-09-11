#include "readelf.h"

/**
 * print_section_header_table_size - prints size of header table entry
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_section_header_table_size(ehdr_t *e)
{
	Elf64_Half shentsize = e->e64.e_shentsize;

	E_SET_ENDIAN(shentsize);
	printf(LABEL"%d (bytes)\n", "Size of section headers:", shentsize);
	return (0);
}
