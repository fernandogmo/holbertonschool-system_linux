#include "readelf.h"
#include "machines.h"

/**
 * print_machine - prints the target machine type
 * @e: pointer to elf header struct
 * Return: 0
 */
int print_machine(Elf64_Ehdr *e)
{
	uint8_t   data = e->e_ident[EI_DATA];
	Elf64_Half idx = e->e_machine;

	idx = (data == ELFDATA2MSB) ? be64toh(idx) :
	      (data == ELFDATA2LSB) ? le64toh(idx) : idx;
	{
		const char *m = machines[idx];

		if (m)
			printf(LABEL"%s\n", "Machine:", m);
		else
			printf("<unknown>: %#x\n", idx);
	}
	return (0);
}
