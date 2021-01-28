#include "readelf.h"

/**
 * print_magic - prints the 16 bytes of ELF header
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_magic(Elf64_Ehdr *e)
{
	size_t i = 0;

	printf("  Magic:   ");
	while (i < EI_NIDENT)
		printf("%.2x ", e->e_ident[i++]);
	printf("\n");

	return (0);
}
