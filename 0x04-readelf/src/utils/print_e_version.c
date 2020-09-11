#include "readelf.h"

/**
 * print_e_version - prints the e_version value
 **		     THIS SHOULD ALWAYS BE 1
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_e_version(ehdr_t *e)
{
	Elf64_Word version = e->e64.e_version;

	E_SET_ENDIAN(version);
	printf(LABEL"%#x\n", "Version:", version);
	return (0);
}
