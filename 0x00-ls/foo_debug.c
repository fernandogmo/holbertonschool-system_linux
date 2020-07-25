#include "hls.h"

/**
 * dbg_print_array - Prints pathnames in an array of file_t pointers
 *
 * @array: The array to be printed
 * @size: Number of elements in @array
 */
void dbg_print_array(file_t **array, size_t size)
{
	size_t i;

	i = 0;
	while (array && i < size)
	{
		if (i > 0)
			printf(", ");
		printf("%s", array[i]->path);
		++i;
	}
	printf("\n");
}

/**
 * dbg_swap - swaps two values in file_t pointer array if they are not equal,
 *        and prints the current state of the array it was first called with.
 * @a: first value to swap
 * @b: second value to swap
 * @array: pointer to first element of initial array
 * @size: full size of initial array
 */
void dbg_swap(file_t **a, file_t **b, file_t **array, size_t size)
{
	/* for printing */
	static file_t **ptr;
	static size_t s;

	file_t *tmp = *a;

	if (*a != *b)
	{
		*a = *b;
		*b = tmp;
		if (!ptr)
			ptr = array, s = size;
		dbg_print_array(ptr, s);
	}
}


/**
  * dbg_print_binary - prints the binary representation of a number
  * @n: unsigned char decimal
  */
void dbg_print_binary(unsigned char n)
{
	int begin = 0, bit_offset = sizeof(n) * 8;
	unsigned char bit  = 1 << (bit_offset - 1);

	while (bit)
	{
		begin = (bit & n) ? 1 : begin;
		if (begin)
			(bit & n) ? putchar('1') : putchar('0');
		bit >>= 1;
	}
	if (n == 0)
		putchar('0');
}

