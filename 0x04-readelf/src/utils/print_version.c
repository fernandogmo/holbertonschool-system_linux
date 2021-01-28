#include "readelf.h"


/**
 * print_version - prints the ELF version
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_version(Elf64_Ehdr *e)
{
	uint8_t v = e->e_ident[EI_VERSION];

	if (v == EV_CURRENT)
		printf(LABEL"%d (current)\n", "Version:", v);
	else if (e->e_ident[EI_VERSION] != EV_NONE)
		printf(LABEL"<unknown: %x\n", "Version:", v);
	return (0);
}
