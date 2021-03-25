#include "hnm.h"

/**
 * get_sym_ndx - Get symbol section index
 * @sym_table: symbol
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: section index
 */
uint16_t get_sym_ndx(unsigned char *sym_table, int class, int endianess)
{
	uint16_t shndx = class == ELFCLASS32 ?
		((Elf32_Sym *) sym_table)->st_shndx :
		((Elf64_Sym *) sym_table)->st_shndx;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &shndx, class == ELFCLASS32 ? 2 : 2);

	return (shndx);
}

/**
 * get_sym_type_2 - Get symbol type
 * @st_type: symbol table type
 * @st_bind: symbol table bind
 * @shndx: section header index
 * Return: symbol type
 */
char get_sym_type_2(int st_type, int st_bind, uint16_t shndx)
{
	char c;

	if (st_bind == STB_GNU_UNIQUE)
		c = 'u';
	else if (st_bind == STB_WEAK && st_type == STT_OBJECT)
		c = shndx == SHN_UNDEF ? 'v' : 'V';
	else if (st_bind == STB_WEAK)
		c = shndx == SHN_UNDEF ? 'w' : 'W';
	else if (shndx == SHN_UNDEF)
		c = 'U';
	else if (shndx == SHN_ABS)
		c = 'A';
	else if (shndx == SHN_COMMON)
		c = 'C';
	else
		return (-1);
	return (c);
}

/**
 * get_sh_type - Get section header
 * @data: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: section header type
 */
uint32_t get_sh_type(unsigned char *data, int class, int endianess)
{
	uint32_t type = class == ELFCLASS32 ?
		((Elf32_Shdr *) data)->sh_type :
		((Elf64_Shdr *) data)->sh_type;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &type, class == ELFCLASS32 ? 4 : 4);

	return (type);
}

/**
 * get_sh_flg - Get section header flags
 * @data: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: section header flags
 */
uint64_t get_sh_flg(unsigned char *data, int class, int endianess)
{
	uint64_t flags = class == ELFCLASS32 ?
		((Elf32_Shdr *) data)->sh_flags :
		((Elf64_Shdr *) data)->sh_flags;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &flags, class == ELFCLASS32 ? 4 : 8);

	return (flags);
}

/**
 * get_sym_type_3 - Get symbol type
 * @shndx: section header index
 * @sh_type: section header type
 * @sh_flags: section header flags
 * Return: symbol type
 */
char get_sym_type_3(uint16_t shndx, uint32_t sh_type, uint64_t sh_flags)
{
	char c;

	(void) shndx;
	if (sh_type == SHT_NOBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'B';
	else if (sh_type == SHT_PROGBITS && sh_flags == SHF_ALLOC)
		c = 'R';
	else if (sh_type == SHT_PROGBITS && sh_flags == (SHF_ALLOC | SHF_WRITE))
		c = 'D';
	else if (sh_type == SHT_PROGBITS && sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		c = 'T';
	else if (sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = 'T';
	return (c);
}
