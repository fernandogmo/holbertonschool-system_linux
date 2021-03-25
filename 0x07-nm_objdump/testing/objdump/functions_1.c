#include "objdump.h"

/**
 * get_file_frmt - get file format
 * @cls: 32 or 64 bit
 * @data: ELFDATA2MSB or ELFDATA2LSB
 * Return: file format string
 */
static char *get_file_frmt(int cls, int data)
{
	if (cls == ELFCLASS32 && data == ELFDATA2MSB)
		return ("elf32-big");
	if (cls == ELFCLASS32)
		return ("elf32-i386");
	return ("elf64-x86-64");
}

/**
 * get_arch - get file architecture
 * @cls: 32 or 64 bit
 * @data: ELFDATA2MSB or ELFDATA2LSB
 * Return: file architecture string
 */
static char *get_arch(int cls, int data)
{
	if (cls == ELFCLASS32 && data == ELFDATA2MSB)
		return ("UNKNOWN!");
	if (cls == ELFCLASS32)
		return ("i386");
	return ("i386:x86-64");
}

/**
 * get_syms_flag - checks if elf file has symbol table
 * @elf: elf headers
 * Return: flag
 */
int get_syms_flag(elf_t *elf)
{
	int flag = 0, i;
	uint32_t type;
	size_t s_size = elf->shdr.entsize;

	for (i = 0; i < elf->shdr.num; ++i)
	{
		type = GET_SHDR(elf->cls, ((uint8_t *)(elf->shdr.addr) + i * s_size),
						sh_type);
		CONVERT(elf->data, type, elf->cls, 4, 4);
		if (type == SHT_SYMTAB || type == SHT_DYNSYM)
		{
			flag |= HAS_SYMS;
			break;
		}
	}
	return (flag);
}

/**
 * get_flags - sets flags
 * @elf: elf headers
 * Return: flag bitfield
 */
int get_flags(elf_t *elf)
{
	int flags = 0;
	uint16_t type = GET_EHDR(elf->cls, elf->ehdr, e_type);

	CONVERT(elf->data, type, elf->cls, 2, 2);

	switch (type)
	{
	case (ET_DYN):
		flags |= DYNAMIC;
		break;
	case (ET_EXEC):
		flags |= EXEC_P;
		break;
	case (ET_REL):
		flags |= HAS_RELOC;
		break;
	case (WP_TEXT):
		flags |= WP_TEXT;
		break;
	case (HAS_LOCALS):
		flags |= HAS_LOCALS;
		break;
	case (HAS_LINENO):
		flags |= HAS_LINENO;
		break;
	case (HAS_DEBUG):
		flags |= HAS_DEBUG;
		break;
	case (BFD_NO_FLAGS):
		flags |= BFD_NO_FLAGS;
		break;
	default:
		break;
	}

	if (elf->phdr.num > 0)
		flags |= D_PAGED;
	flags |= get_syms_flag(elf);

	return (flags);
}

/**
 * print_file_headers - Print file headers, like objdump -f
 * @elf: elf headers
 */
void print_file_headers(elf_t *elf)
{
	Elf64_Off addr;
	int flags = get_flags(elf);

	addr = GET_EHDR(elf->cls, elf->ehdr, e_entry);
	CONVERT(elf->data, addr, elf->cls, 4, 8);
	printf("\n%s:     file format %s\n", elf->file,
		   get_file_frmt(elf->cls, elf->data));
	printf("architecture: %s, flags %#010x:\n",
		   get_arch(elf->cls, elf->data), flags);
	print_flags(flags);
	printf("start address 0x%0*lx\n\n", elf->cls == ELFCLASS32 ? 8 : 16, addr);
}
