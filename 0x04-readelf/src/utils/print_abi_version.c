#include "readelf.h"

/**
 * print_abi_version  - prints target ABI
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_abi_version(Elf64_Ehdr *e)
{
	printf(LABEL"%d\n", "ABI Version:", e->e_ident[EI_ABIVERSION]);
	return (0);
}
