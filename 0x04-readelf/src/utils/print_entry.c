#include "readelf.h"

/**
 * print_entry - prints the ELF entry point address
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_entry(ehdr_t *e)
{
	Elf64_Addr entry = e->e64.e_entry;

	E_SET_ENDIAN(entry);
	printf(LABEL"0x%lx\n", "Entry point address:", entry);
	return (0);
}
