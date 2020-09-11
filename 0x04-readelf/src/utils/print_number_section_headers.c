#include "readelf.h"

/**
 * print_number_section_headers - prints number of section headers
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_number_section_headers(ehdr_t *e)
{
	Elf64_Half shnum = e->e64.e_shnum;

	E_SET_ENDIAN(shnum);
	printf(LABEL"%d\n", "Number of section headers:", shnum);
	return (0);
}
