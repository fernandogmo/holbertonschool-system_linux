#include "readelf.h"

/**
 * print_number_program_headers - prints number of program headers
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_number_program_headers(ehdr_t *e)
{
	Elf64_Half phnum = e->e64.e_phnum;

	E_SET_ENDIAN(phnum);
	printf(LABEL"%d\n", "Number of program headers:", phnum);
	return (0);
}
