#include "readelf.h"

/**
 * print_elf_header - prints formatted from values in file header
 * @e: union of Elf64_Ehdr and Elf32_Ehdr to print from
 * Return: 0
 */
int print_elf_header(ehdr_t *e)
{
	printf("ELF Header:\n");
	print_magic(&e->e64);
	print_class(&e->e64);
	print_data(&e->e64);
	print_version(&e->e64);
	print_osabi(&e->e64);
	print_abi_version(&e->e64);
	print_type(&e->e64);
	print_machine(&e->e64);
	print_e_version(e);
	print_entry(e);
	print_start_program_headers(e);
	print_start_section_headers(e);
	print_flags(e);
	print_elf_header_size(e);
	print_program_header_table_size(e);
	print_number_program_headers(e);
	print_section_header_table_size(e);
	print_number_section_headers(e);
	print_section_header_names_index(e);
	return (0);
}
