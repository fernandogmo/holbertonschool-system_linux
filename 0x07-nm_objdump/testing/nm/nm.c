#include "hnm.h"

/**
 * get_sym_type - Get symbol type
 * @sym_table: symbol table
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * @sh_headers: section headers array
 * Return: symbol type
 */
char get_sym_type(unsigned char *sym_table, int class,
				  int endianess, unsigned char *sh_headers)
{
	unsigned char st_info = class == ELFCLASS32 ?
		((Elf32_Sym *) sym_table)->st_info :
		((Elf64_Sym *) sym_table)->st_info;
	int st_type = ELF32_ST_TYPE(st_info);
	int st_bind = ELF32_ST_BIND(st_info);
	uint16_t shndx = get_sym_ndx(sym_table, class, endianess);
	uint32_t sh_type = 0;
	uint64_t sh_flags = 0;
	char c;

	c = get_sym_type_2(st_type, st_bind, shndx);
	if (c == -1)
	{
		if (shndx != SHN_ABS && shndx != SHN_COMMON)
		{
			sh_type = get_sh_type(sh_headers, class, endianess);
			sh_flags = get_sh_flg(sh_headers, class, endianess);
		}
		c = get_sym_type_3(shndx, sh_type, sh_flags);
	}

	if (st_bind == STB_LOCAL) /* FIXME: ???*/
		c += 32;
	return (c);
}

/**
 * print_symbol_table_entries - Print symbol table entries
 * @sym_table: symbol
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * @str_table: string table
 * @s_size: symbol size
 * @sh_ent_size: section header entry size
 * @sh_headers: section headers array
 * @sh_size: section header size
 */
void print_symbol_table_entries(unsigned char *sym_table, int class,
								int endianess, unsigned char *str_table,
								uint64_t s_size, uint64_t sh_ent_size,
								unsigned char *sh_headers, uint16_t sh_size)
{
	uint64_t n_sym = s_size / sh_ent_size;
	uint64_t i, sym_value, size;
	uint16_t shndx;
	uint32_t name_idx;
	char c;

	for (i = 0; i < n_sym; ++i, sym_table += sh_ent_size)
	{
		size = get_sym_size(sym_table, class, endianess);
		shndx = get_sym_ndx(sym_table, class, endianess);
		name_idx = get_sym_name_idx(sym_table, class, endianess);
		sym_value = get_sym_value(sym_table, class, endianess);
		if (!*(str_table + name_idx) || (!size && !sym_value && shndx == 65521))
			continue;
		if ((size || sym_value) && shndx != 0)
			printf("%0*lx ", class == ELFCLASS32 ? 8 : 16, sym_value);
		else
			printf("%*s ", class == ELFCLASS32 ? 8 : 16, " ");
		c = get_sym_type(sym_table, class, endianess, sh_headers + shndx * sh_size);
		printf("%c %s\n", c, str_table + name_idx);
	}
	free(sym_table - i * sh_ent_size);
	free(sh_headers);
	free(str_table);
}

/**
 * print_symbol_table - gets ready all headers before printing
 * @bytes: character array
 * @filename: elf file
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: 1 if no symbols, 0 otherwise
 */
int print_symbol_table(unsigned char *bytes, char *filename, int class,
			  int endianess)
{
	void *p = get_section_header_off(bytes, class, endianess);
	Elf64_Off offset = class == ELFCLASS32 ? *(Elf32_Off *) p : *(Elf64_Off *) p;
	unsigned char *sh_headers = NULL, *sym_table = NULL, *str_table = NULL;
	uint64_t s_off, s_size, sh_esize;
	uint16_t n_sections = get_num_section_headers(bytes, class, endianess);
	uint16_t sh_size = get_section_hsize(bytes, class, endianess);
	int sym;

	if (read_bytes(&sh_headers, filename, offset, n_sections * sh_size))
		exit(EXIT_FAILURE);
	sym = get_sh_idx_by_type(sh_headers, class, endianess,
							 SHT_SYMTAB, n_sections, sh_size);
	if (sym != -1)
	{
		s_off = get_section_off(sh_headers + ((sym + 1) * sh_size),
								class, endianess);
		s_size = get_section_size(sh_headers + ((sym + 1) * sh_size),
								  class, endianess);
		if (read_bytes(&str_table, filename, s_off, s_size))
		{
			free(sh_headers);
			exit(EXIT_FAILURE);
		}
		s_off = get_section_off(sh_headers + (sym * sh_size), class, endianess);
		s_size = get_section_size(sh_headers + (sym * sh_size), class, endianess);
		sh_esize = get_section_es(sh_headers + (sym * sh_size), class, endianess);
		if (read_bytes(&sym_table, filename, s_off, s_size))
		{
			free(sh_headers), free(str_table);
			exit(EXIT_FAILURE);
		}
		print_symbol_table_entries(sym_table, class, endianess, str_table,
								   s_size, sh_esize, sh_headers, sh_size);
	}
	else
	{
		free(sh_headers);
		return (1);
	}
	return (0);
}

/**
 * nm - nm -p command implementation
 * @cmd: name of executable
 * @filename: filename
 * @n_files: number of files
 * Return: 0 if success, 1 if failure
 */
int nm(char *cmd, char *filename, int n_files)
{
	unsigned char bytes[64];
	int res;

	if (access(filename, F_OK) == -1)
	{
		fprintf(stderr, "%s: '%s': No such file\n", cmd, filename);
		return (1);
	}

	if (read_elf_header_bytes(bytes, filename))
		return (1);
	if (access(filename, R_OK) == -1)
	{
		fprintf(stderr, "%s: %s: Permission denied\n", cmd, filename);
		return (EXIT_FAILURE);
	}

	if (check_elf(bytes))
	{
		fprintf(stderr, "%s: %s: File format not recognized\n", cmd, filename);
		return (1);
	}

	if (n_files > 1)
		printf("\n%s:\n", filename);

	res = print_symbol_table(bytes, filename,
					   bytes[4] == ELFCLASS32 ? ELFCLASS32 : ELFCLASS64,
					   bytes[5] == ELFDATA2MSB ? ELFDATA2MSB : ELFDATA2LSB);
	if (res)
		fprintf(stderr, "%s: %s: no symbols\n", cmd, filename);
	return (0);
}

/**
 * main - Entry point, nm -p
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 otherwise
 */
int main(int argc, char *argv[])
{
	char *def = "a.out";
	int n_files = argc - 1, i;
	int ret = 0;

	if (argc < 2)
		argv[1] = def, ++n_files;

	for (i = 1; i <= n_files; ++i)
	{
		ret += nm(argv[0], argv[i], n_files);
	}

	return (ret);
}
