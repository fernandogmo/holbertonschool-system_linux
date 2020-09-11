#include "readelf.h"

/**
 * print_elf_header_size - prints the size of elf file header
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_elf_header_size(ehdr_t *e)
{
	Elf64_Half ehsize = e->e64.e_ehsize;

	E_SET_ENDIAN(ehsize);
	printf(LABEL"%d (bytes)\n", "Size of this header:", ehsize);
	return (0);
}
