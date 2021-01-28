#include "readelf.h"

/**
 * print_data - prints the endianness type
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_data(Elf64_Ehdr *e)
{
	char *s, t[15];
	unsigned char c = e->e_ident[EI_DATA];

	s = (c == ELFDATA2LSB) ? "2's complement, little endian" :
	    (c == ELFDATA2MSB) ? "2's complement, big endian" :
	    (c == ELFDATANONE) ? "none" : (sprintf(t, "<unknown: %#x>", c), t);
	printf(LABEL"%s\n", "Data:", s);
	return (0);
}
