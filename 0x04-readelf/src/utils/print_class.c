#include "readelf.h"

/**
 * print_class - prints the byte architecture class
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_class(Elf64_Ehdr *e)
{
	char *s, buf[15];
	uint8_t c = e->e_ident[EI_CLASS];

	s = (c == ELFCLASS64) ? "ELF64" :
	    (c == ELFCLASS32) ? "ELF32" :
	    (c == ELFCLASSNONE) ? "none" :
		(sprintf(buf, "<unknown: %#x>", c), buf);
	printf(LABEL"%s\n", "Class:", s);
	return (0);
}
