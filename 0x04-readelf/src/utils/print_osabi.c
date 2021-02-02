#include "readelf.h"

/**
 * print_osabi - prints OS ABI version
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_osabi(Elf64_Ehdr *e)
{
	char *s, buf[15];
	uint8_t os = e->e_ident[EI_OSABI];

	s = (os == ELFOSABI_NONE) ? "UNIX - System V" :
	    (os == ELFOSABI_HPUX) ? "UNIX - HP-UX" :
	    (os == ELFOSABI_NETBSD) ? "UNIX - NetBSD" :
	    (os == ELFOSABI_LINUX) ? "UNIX - Linux" :
	    (os == ELFOSABI_SOLARIS) ? "UNIX - Solaris" :
	    (os == ELFOSABI_AIX) ? "UNIX - AIX" :
	    (os == ELFOSABI_IRIX) ? "UNIX - IRIX" :
	    (os == ELFOSABI_FREEBSD) ? "UNIX - FreeBSD" :
	    (os == ELFOSABI_TRU64) ? "UNIX - TRU64" :
	    (os == ELFOSABI_OPENBSD) ? "UNIX - OpenBSD" :
	    (os == ELFOSABI_STANDALONE) ? "Standalone App" :
	    (os == ELFOSABI_ARM) ? "ARM" :
		(sprintf(buf, "<unknown: %x>", os), buf);
	printf("  %-35s%s\n", "OS/ABI:", s);
	return (0);
}
