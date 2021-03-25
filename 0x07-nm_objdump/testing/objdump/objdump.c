#include "objdump.h"

/**
 * objdump - objdump -sf like printing
 * @elf: elf sections
 */
void objdump(elf_t *elf)
{
	uint8_t *sh_strtab;
	uint16_t indx, sh_size = elf->shdr.entsize;
	Elf64_Off str_off;

	indx = GET_EHDR(elf->cls, elf->ehdr, e_shstrndx);
	CONVERT(elf->data, indx, elf->cls, 2, 2);
	str_off = GET_SHDR(elf->cls, ((uint8_t *)(elf->shdr.addr) + sh_size * indx),
					   sh_offset);
	CONVERT(elf->data, str_off, elf->cls, 4, 8);
	sh_strtab = (uint8_t *)(elf->ehdr) + str_off;
	print_file_headers(elf);
	print_sections(elf, sh_strtab);
}

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
 * entry - loops over elf files and calls objdump
 * @cmd: name of the executable
 * @filename: file name
 * Return: 0 on success, 1 on failure
 */
int entry(char *cmd, char *filename)
{
	struct stat st;
	elf_t elf;
	int ret;

	if (access(filename, F_OK) == -1)
	{
		fprintf(stderr, "%s: '%s': No such file\n", cmd, filename);
		return (EXIT_FAILURE);
	}

	if (access(filename, R_OK) == -1)
	{
		fprintf(stderr, "%s: %s: Permission denied\n", cmd, filename);
		return (EXIT_FAILURE);
	}

	if (stat(filename, &st) == -1)
	{
		return (EXIT_FAILURE);
	}
	elf.file_size = st.st_size;
	elf.file = filename;
	ret = init_elf(&elf);
	if (ret == 2)
	{
		fprintf(stderr, "%s: %s: File format not recognized\n", cmd, filename);
		return (EXIT_FAILURE);
	}
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	objdump(&elf);
	munmap(elf.ehdr, elf.file_size);
	return (EXIT_SUCCESS);
}

/**
 * main - Entry point, objdump -sf
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
		if (entry(argv[0], argv[i]))
			ret = EXIT_FAILURE;
	}

	return (ret);
}
