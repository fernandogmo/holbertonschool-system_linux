#include "hnm.h"

/**
 * reverse - Reverse char array, used to go from MSB -> LSB
 * @bytes: character array
 * @size: size of @bytes
*/
void reverse(unsigned char *bytes, size_t size)
{
	size_t start = 0, end = size - 1;
	int temp;

	while (start < end)
	{
		temp = bytes[start];
		bytes[start] = bytes[end];
		bytes[end] = temp;
		start++;
		end--;
	}
}

/**
 * read_elf_header_bytes - Reads 64 bytes from file and stores in @bytes
 * @bytes: character array
 * @filename: elf file
 * Return: 0 on success, 1 otherwise
*/
int read_elf_header_bytes(unsigned char *bytes, const char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "rb");
	if (!fp || fread(bytes, 64, 1, fp) == 0)
	{
		return (1);
	}

	fclose(fp);
	return (0);
}

/**
 * check_elf - Checks if it is an elf file
 * @bytes: character array
 * Return: 0 on success, 1 otherwise
 */
int check_elf(unsigned char *bytes)
{
	Elf64_Ehdr *header64;

	header64 = (Elf64_Ehdr *) bytes;

	if (memcmp(header64->e_ident, ELFMAG, SELFMAG) != 0)
	{
		return (1);
	}
	return (0);
}

/**
 * get_section_header_off - Print section headers
 * @bytes: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: void pointer to offset
 */
void *get_section_header_off(unsigned char *bytes, int class, int endianess)
{
	void *header_off = class == ELFCLASS32 ?
		(void *) &((Elf32_Ehdr *) bytes)->e_shoff :
		(void *) &((Elf64_Ehdr *) bytes)->e_shoff;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) header_off, class == ELFCLASS32 ? 4 : 8);

	return (header_off);
}

/**
 * get_section_off - Get section offset
 * @bytes: character array
 * @class: ELFCLASS32 or ELFCLASS64
 * @endianess: LSB or MSB
 * Return: section offset
 */
Elf64_Off get_section_off(unsigned char *bytes, int class, int endianess)
{
	Elf64_Off off = class == ELFCLASS32 ?
		((Elf32_Shdr *) bytes)->sh_offset :
		((Elf64_Shdr *) bytes)->sh_offset;

	if (endianess == ELFDATA2MSB)
		reverse((unsigned char *) &off, class == ELFCLASS32 ? 4 : 8);

	return (off);
}
