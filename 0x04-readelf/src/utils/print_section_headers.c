#include "readelf.h"

int read_section_headers(shdr_t *s, ehdr_t *e, FILE* f)
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

int read_section_names(const char **names, shdr_t *s)
{
	(void)names;
	(void)s;
	return (0);
}
int print_section_headers_values(shdr_t *s, ehdr_t *e)
{
	int i = 0;
	char *names;
	uint8_t *sp = &s->s64;
#define INIT_SH_VARS(shdr) \
	addr = (Elf64_Shdr *)shdr->sh_addr; \
	addralign = shdr->sh_addralign;\
	entsize = shdr->sh_entsize;\
	flags = shdr->sh_flags;\
	size = shdr->sh_size;\
	info = shdr->sh_info;\
	link = shdr->sh_link;\
	type = shdr->sh_type\
	S_SET_ENDIAN(addr);\
	S_SET_ENDIAN(addralign);\
	S_SET_ENDIAN(entsize);\
	S_SET_ENDIAN(flags);\
	S_SET_ENDIAN(size);\
	S_SET_ENDIAN(info);\
	S_SET_ENDIAN(link);\
	S_SET_ENDIAN(type)

	Elf64_Addr addr;
	Elf64_Xword addralign, entsize, flags, size;
	Elf64_Word name, info, link, type;


	Elf64_Half     shnum = e->e64.e_shnum;
	Elf64_Half shentsize = e->e64.e_shentsize;
	Elf64_Half shstrndx = e->e64.e_shstrndx;
 	E_SET_ENDIAN(shnum);
 	E_SET_ENDIAN(shentsize);
	E_SET_ENDIAN(shstrndx);

	names = (char *)&s->s64 + shstrndx;
	for (; i < shnum; sp += shentsize)
	{
		INIT_SH_VARS(sp);
		printf("  [%2d] ", i++);
		printf("%-17s\n", names + name);
	}
	(void)names;
	return (0);
}
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


