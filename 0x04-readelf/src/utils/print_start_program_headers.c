#include "readelf.h"

/**
 * print_start_program_headers - prints address of program header table
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_start_program_headers(ehdr_t *e)
{
	Elf64_Addr phoff = e->e64.e_phoff;

	E_SET_ENDIAN(phoff);
	printf(LABEL"%ld (bytes into file)\n",
		"Start of program headers:", phoff);
	return (0);
}
