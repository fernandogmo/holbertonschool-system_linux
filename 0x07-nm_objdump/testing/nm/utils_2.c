#include "hnm.h"

/**
 * get_num_section_headers - get number of section headers
 * @bytes: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: number of section headers
 */
uint16_t get_num_section_headers(unsigned char *bytes, int class,
				 int endianess)
{
	uint16_t shnum = class == ELFCLASS32 ?
		((Elf32_Ehdr *) bytes)->e_shnum :
		((Elf64_Ehdr *) bytes)->e_shnum;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &shnum, 2);
	return (shnum);
}

/**
 * read__bytes - Reads 64 bytes from file and stores in @bytes
 * @bytes: character array
 * @filename: elf file
 * @offset: offset of file
 * @size: how many bytes to read
 * Return: 0 on success, 1 otherwise
 */
int read_bytes(unsigned char **bytes, const char *filename, size_t offset,
	       size_t size)
{
	FILE *fp = NULL;

	*bytes = malloc(sizeof(char) * size);
	if (!bytes)
		exit(EXIT_FAILURE);
	fp = fopen(filename, "rb");
	if (!fp || fseek(fp, offset, SEEK_SET) || fread(*bytes, size, 1, fp) == 0)
	{
		perror(NULL);
		return (1);
	}
	fclose(fp);
	return (0);
}

/**
 * get_string_table_idx - Print Section header string table index
 * @bytes: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: index of string table section
 */
uint16_t get_string_table_idx(unsigned char *bytes, int class, int endianess)
{
	uint16_t shstrndx = class == ELFCLASS32 ?
		((Elf32_Ehdr *) bytes)->e_shstrndx :
		((Elf64_Ehdr *) bytes)->e_shstrndx;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &shstrndx, 2);

	return (shstrndx);
}

/**
 * get_section_size- Gets section size
 * @bytes: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: section size
 */
uint64_t get_section_size(unsigned char *bytes, int class, int endianess)
{
	uint64_t size = class == ELFCLASS32 ?
		((Elf32_Shdr *) bytes)->sh_size :
		((Elf64_Shdr *) bytes)->sh_size;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &size, class == ELFCLASS32 ? 4 : 8);

	return (size);
}

/**
 * get_section_hsize - get section size
 * @bytes: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: section size
 */
uint16_t get_section_hsize(unsigned char *bytes, int class, int endianess)
{
	uint16_t shentsize = class == ELFCLASS32 ?
		((Elf32_Ehdr *) bytes)->e_shentsize :
		((Elf64_Ehdr *) bytes)->e_shentsize;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &shentsize, 2);
	return (shentsize);
}
