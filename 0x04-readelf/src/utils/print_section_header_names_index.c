#include "readelf.h"

/**
 * print_section_header_names_index - prints index of section header table
 **				      entry that contains the section names.
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_section_header_names_index(ehdr_t *e)
{
	Elf64_Half shstrndx = e->e64.e_shstrndx;

	E_SET_ENDIAN(shstrndx);
	printf(LABEL"%d\n", "Section header string table index:", shstrndx);
	return (0);
}

