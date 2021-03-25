#include "hnm.h"

/**
 * get_sh_idx_by_type - Get section header idx
 * @sh_headers: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * @sh_type: section header type
 * @n_sh: number of section headers
 * @sh_size: section header size
 * Return: section entry size
 */
int get_sh_idx_by_type(unsigned char *sh_headers, int class, int endianess,
					   uint32_t sh_type, short n_sh, short sh_size)
{
	int i;
	uint32_t type;

	for (i = 0; i < n_sh; ++i, sh_headers += sh_size)
	{
		type = class == ELFCLASS32 ?
			((Elf32_Shdr *) sh_headers)->sh_type :
			((Elf64_Shdr *) sh_headers)->sh_type;

		if (endianess == ELFDATA2MSB)
			reverse((unsigned char *) &type, 4);

		if (type == sh_type)
			return (i);
	}

	return (-1);
}

/**
 * get_section_es - Get section entry size
 * @data: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: section entry size
 */
uint64_t get_section_es(unsigned char *data, int class, int endianess)
{
	uint64_t entsize = class == ELFCLASS32 ?
		((Elf32_Shdr *) data)->sh_entsize :
		((Elf64_Shdr *) data)->sh_entsize;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &entsize, class == ELFCLASS32 ? 4 : 8);
	return (entsize);
}

/**
 * get_sym_size - Get symbol size
 * @sym_table: symbol
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: symbol size
 */
uint64_t get_sym_size(unsigned char *sym_table, int class, int endianess)
{
	uint64_t size = class == ELFCLASS32 ?
		((Elf32_Sym *) sym_table)->st_size :
		((Elf64_Sym *) sym_table)->st_size;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &size, class == ELFCLASS32 ? 4 : 8);

	return (size);
}

/**
 * get_sym_value - Get symbol value
 * @sym_table: symbol
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: symbol value
 */
Elf64_Addr get_sym_value(unsigned char *sym_table, int class, int endianess)
{
	Elf64_Addr value = class == ELFCLASS32 ?
		((Elf32_Sym *) sym_table)->st_value :
		((Elf64_Sym *) sym_table)->st_value;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &value, class == ELFCLASS32 ? 4 : 8);

	return (value);
}

/**
 * get_sym_name_idx - Get symbol name idx
 * @sym_table: symbol
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: symbol name idx
 */
uint32_t get_sym_name_idx(unsigned char *sym_table, int class, int endianess)
{
	uint32_t idx = class == ELFCLASS32 ?
		((Elf32_Sym *) sym_table)->st_name :
		((Elf64_Sym *) sym_table)->st_name;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &idx, class == ELFCLASS32 ? 4 : 4);

	return (idx);
}
