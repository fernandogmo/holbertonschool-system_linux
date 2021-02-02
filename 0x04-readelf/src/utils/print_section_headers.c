#include "readelf.h"


/**
 * read_section_headers - it does this
 * @s: shdr
 * @e: ehdr
 * @f: FILE
 * Return: 0
 */
int read_section_headers(shdr_t *s, ehdr_t *e, FILE *f)
{
	Elf64_Addr     shoff = e->e64.e_shoff;
	Elf64_Half     shnum = e->e64.e_shnum;
	Elf64_Half shentsize = e->e64.e_shentsize;

	E_SET_ENDIAN(shoff);
	E_SET_ENDIAN(shnum);
	E_SET_ENDIAN(shentsize);

	/* TODO catch errors in following: */
	fseek(f, shoff, SEEK_SET);
	fread(&s->s64, 1, (shnum * shentsize), f);
	/* I hate doing this here but since I have them available... */
	printf("There are %d section headers, starting at offset 0x%x:\n\n",
		(int)shnum, (unsigned int)shoff);
	return (0);
}

/**
 * read_section_names - it does this
 * @names: string array
 * @s: shdr
 * Return: 0
 */
int read_section_names(const char **names, shdr_t *s)
{
	(void)names;
	(void)s;
	return (0);
}

/**
 * print_section_headers_values - it does this
 * @s: shdr
 * @e: ehdr
 * Return: 0
 */
int print_section_headers_values(shdr_t *s, ehdr_t *e)
{
	int i = 0;
	char *names;
	Elf64_Shdr *sp = &s->s64;

	Elf64_Addr addr;
	Elf64_Xword addralign, entsize, flags, size;
	Elf64_Word name = 0, info, link, type;

	Elf64_Half     shnum = e->e64.e_shnum;
	Elf64_Half shentsize = e->e64.e_shentsize;
	Elf64_Half shstrndx = e->e64.e_shstrndx;

	E_SET_ENDIAN(shnum);
	E_SET_ENDIAN(shentsize);
	E_SET_ENDIAN(shstrndx);

	names = (char *)&s->s64 + shstrndx;
	for (; i < shnum; sp += shentsize)
	{
		INIT_SHDR_VARS(sp);
		printf("  [%2d] ", i++);
		printf("%-17s\n", names + name);
	}
	(void)names;
	return (0);
}

/**
 * print_section_headers - it does this
 * @s: shdr
 * @e: ehdr
 * Return: 0
 */
int print_section_headers(shdr_t *s, ehdr_t *e)
{
	uint8_t class = e->e64.e_ident[EI_DATA];

	printf("Section Headers:\n");
	printf("  [Nr] Name              Type            ");
	if (class == ELFCLASS32)
		printf("Addr     Off    Size   ES Flg Lk Inf Al\n");
	else
		printf("Address          Off    Size   ES Flg Lk Inf Al\n");
	print_section_headers_values(s, e);
	return (0);
}


