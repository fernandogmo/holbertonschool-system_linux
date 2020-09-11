#include "readelf.h"
#include <err.h>

/**
 * print_type - prints the ELF type
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_type(Elf64_Ehdr *e)
{
	char *s, buf[15];
	uint8_t data = e->e_ident[EI_DATA];
	Elf64_Half t = e->e_type;

	t = (data == ELFDATA2MSB) ? be32toh(t) :
	    (data == ELFDATA2LSB) ? le32toh(t) :
		(errx(EXIT_FAILURE, "Invalid data encoding"), t);
	s = (t == ET_NONE) ? "NONE (None)" :
	    (t == ET_REL) ? "REL (Relocatable file)" :
	    (t == ET_EXEC) ? "EXEC (Executable file)" :
	    (t == ET_DYN) ? "DYN (Shared object file)" :
	    (t == ET_CORE) ? "CORE (Core file)" :
		(sprintf(buf, "<unknown>: %#x", t), buf);
	printf(LABEL"%s\n", "Type:", s);
	return (0);
}
