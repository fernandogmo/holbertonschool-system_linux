#include "objdump.h"

/**
 * init_phdr - initialize program header
 * @elf: elf headers
 * Return: program header
*/
hdr_t init_phdr(elf_t *elf)
{
	hdr_t phdr;
	Elf64_Off off;
	uint16_t size, num;

	off = GET_EHDR(elf->cls, elf->ehdr, e_phoff);
	size = GET_EHDR(elf->cls, elf->ehdr, e_phentsize);
	num = GET_EHDR(elf->cls, elf->ehdr, e_phnum);

	if (elf->data == ELFDATA2MSB)
	{
		CONVERT(elf->data, off, elf->cls, 4, 8);
		CONVERT(elf->data, size, elf->cls, 2, 2);
		CONVERT(elf->data, num, elf->cls, 2, 2);
	}

	phdr.addr = (uint8_t *)(elf->ehdr) + off;
	phdr.entsize = size;
	phdr.num = num;

	return (phdr);
}

/**
 * init_shdr - initialize section header
 * @elf: elf headers
 * Return: section header
*/
hdr_t init_shdr(elf_t *elf)
{
	hdr_t shdr;
	Elf64_Off off;
	uint16_t size, num;

	off = GET_EHDR(elf->cls, elf->ehdr, e_shoff);
	size = GET_EHDR(elf->cls, elf->ehdr, e_shentsize);
	num = GET_EHDR(elf->cls, elf->ehdr, e_shnum);

	if (elf->data == ELFDATA2MSB)
	{
		CONVERT(elf->data, off, elf->cls, 4, 8);
		CONVERT(elf->data, size, elf->cls, 2, 2);
		CONVERT(elf->data, num, elf->cls, 2, 2);
	}

	shdr.addr = (uint8_t *)(elf->ehdr) + off;
	shdr.entsize = size;
	shdr.num = num;
	return (shdr);
}

/**
 * init_elf - initialize elf headers
 * @elf: elf headers
 * Return: 0 if success, 1 on failure, 2 when file is not elf
*/
int init_elf(elf_t *elf)
{
	int fd;

	fd = open(elf->file, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	elf->ehdr = mmap(NULL, elf->file_size, PROT_READ, MAP_SHARED, fd, 0);
	if (elf->ehdr == MAP_FAILED)
		return (EXIT_FAILURE);
	if (check_elf((uint8_t *)elf->ehdr))
		return (2);
	elf->cls = *(char *)((uint8_t *)(elf->ehdr) + EI_CLASS);
	elf->data = *(char *)((uint8_t *)(elf->ehdr) + EI_DATA);
	elf->phdr = init_phdr(elf);
	elf->shdr = init_shdr(elf);
	return (EXIT_SUCCESS);
}

/**
 * skip_section - tells if section needs to be skipped
 * @elf: elf headers
 * @shdr: nth section header
 * Return: 1 if section needs to be skipped, 0 otherwise
*/
int skip_section(elf_t *elf, void *shdr)
{
	uint64_t size, flags;
	uint32_t type;

	size = GET_SHDR(elf->cls, shdr, sh_size);
	flags = GET_SHDR(elf->cls, shdr, sh_flags);
	type = GET_SHDR(elf->cls, shdr, sh_type);
	CONVERT(elf->data, size, elf->cls, 4, 8);
	CONVERT(elf->data, flags, elf->cls, 4, 8);
	CONVERT(elf->data, type, elf->cls, 4, 4);

	if ((type != SHT_NULL && size != 0 && type != SHT_NOBITS &&
		 type != SHT_SYMTAB && type != SHT_STRTAB &&
		 type != SHT_RELA && type != SHT_REL) ||
		(type == SHT_STRTAB && (flags & SHF_ALLOC)) ||
		(type == SHT_RELA && (flags & SHF_ALLOC)) ||
		(type == SHT_REL && (flags & SHF_ALLOC)))
		return (0);
	return (1);
}

/**
 * print_flags - Print flags from @flags bitfield
 * @flags: flags bitfield
 */
void print_flags(int flags)
{
	int printed = 0;
	int flgs_arr[] = {BFD_NO_FLAGS, HAS_RELOC, EXEC_P, HAS_LINENO, HAS_DEBUG,
		HAS_SYMS, HAS_LOCALS, DYNAMIC, WP_TEXT, D_PAGED};
	char *flgs_names[] = {"BFD_NO_FLAGS", "HAS_RELOC", "EXEC_P", "HAS_LINENO",
		"HAS_DEBUG", "HAS_SYMS", "HAS_LOCALS", "DYNAMIC", "WP_TEXT", "D_PAGED"};
	size_t size = sizeof(flgs_arr) / sizeof(flgs_arr[0]), i;

	for (i = 0; i < size; ++i)
	{
		if (flags & flgs_arr[i])
		{
			printf("%s%s", printed ? ", " : "", flgs_names[i]);
			printed = 1;
		}
	}
	putchar('\n');
}
