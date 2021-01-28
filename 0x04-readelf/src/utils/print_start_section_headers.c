#include "readelf.h"

/**
 * print_start_section_headers - prints address of section header table
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_start_section_headers(ehdr_t *e)
{
	Elf64_Addr shoff = e->e64.e_shoff;

	E_SET_ENDIAN(shoff);
	printf(LABEL"%ld (bytes into file)\n",
		"Start of section headers:", shoff);
	return (0);
}
