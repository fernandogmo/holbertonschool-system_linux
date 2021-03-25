#include "objdump.h"
#include <stdint.h>

/**
 * print_hex - Print hex of sections
 * @bytes: nth section
 * @printed: Number of printed bytes
 * @size: number of total bytes of section
 */
void print_hex(uint8_t *bytes, uint64_t printed, uint64_t size)
{
	size_t i;

	for (i = printed; i < printed + ALIGNMENT; ++i)
	{
		if (i % 4 == 0)
			printf(" ");
		if (i >= size)
			printf("  ");
		else
			printf("%02x", *(bytes + i));
	}
}

/**
 * print_ascii - Print ascii of sections
 * @bytes: nth section
 * @printed: Number of printed bytes
 * @size: number of total bytes of section
 */
void print_ascii(uint8_t *bytes, uint64_t printed, uint64_t size)
{
	size_t i;
	uint8_t c;

	printf("  ");
	for (i = printed; i < printed + ALIGNMENT; ++i)
	{
		if (i >= size)
			printf(" ");
		else
		{
			c = *(bytes + i);
			if (c < 32 || c > 126)
				printf(".");
			else
				printf("%c", c);
		}
	}
}

/**
 * get_width - get address width in hex, for padding
 * @start: start address of section
 * @size: size of the section
 * Return: address width
 */
int get_width(uint64_t start, uint64_t size)
{
	uint64_t hex = 0x1000;
	int width = 4;

	for (hex = 0x10000; hex <= start + size; hex *= 0x10)
		++width;
	return (width);
}

/**
 * print_bytes - Print section bytes, objdump -s
 * @elf: elf headers
 * @shdr: nth section header
 */
void print_bytes(elf_t *elf, void *shdr)
{
	uint64_t size, offset, addr, aligned_size, i;
	int width;

	size = GET_SHDR(elf->cls, shdr, sh_size);
	offset = GET_SHDR(elf->cls, shdr, sh_offset);
	addr = GET_SHDR(elf->cls, shdr, sh_addr);
	CONVERT(elf->data, size, elf->cls, 4, 8);
	CONVERT(elf->data, offset, elf->cls, 4, 8);
	CONVERT(elf->data, addr, elf->cls, 4, 8);
	if (size % ALIGNMENT)
		aligned_size = size + ALIGNMENT - size % ALIGNMENT;
	else
		aligned_size = size;

	width = get_width(addr, aligned_size);
	for (i = 0; i < aligned_size; i += ALIGNMENT)
	{
		printf(" %0*lx", width, addr + i);
		print_hex((uint8_t *)(elf->ehdr) + offset, i, size);
		print_ascii((uint8_t *)(elf->ehdr) + offset, i, size);
		printf("\n");
	}
}

/**
 * print_sections - Print section bytes, like objdump -s
 * @elf: elf headers
 * @str_tab: section string table
 */
void print_sections(elf_t *elf, uint8_t *str_tab)
{
	uint16_t size = elf->shdr.entsize, num = elf->shdr.num;
	void *addr = elf->shdr.addr;
	size_t i;
	uint32_t name = 0;

	for (i = 0; i < num; ++i)
	{
		if (!skip_section(elf, (uint8_t *)(addr) + i * size))
		{
			name = GET_SHDR(elf->cls, (uint8_t *)(addr) + i * size, sh_name);
			CONVERT(elf->data, name, elf->cls, 4, 4);
			printf("Contents of section %s:\n", str_tab + name);
			print_bytes(elf, (uint8_t *)(addr) + i * size);
		}
	}
}
