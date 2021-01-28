#include "readelf.h"

/**
 * print_flags - prints the flags
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_flags(ehdr_t *e)
{
	Elf64_Word flags = e->e64.e_flags;

	E_SET_ENDIAN(flags);
	printf(LABEL"0x%x\n", "Flags:", flags);
	return (0);
}
