#include "hls.h"

/**
 * dbg_print_array - prints pathnames in an array of file_t pointers
 * @array: the array to be printed
 * @size: number of elements in @array
 */
void dbg_print_array(file_t **array, size_t size)
{
	size_t i = 0;

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
  * dbg_print_binary - prints the binary representation of 8-bit integer
  * @n: unsigned char decimal integer
  */
void dbg_print_binary(unsigned char n)
{
	int bits = 8;
	int bit_offset = sizeof(n) * bits;
	unsigned char bit = 1 << (bit_offset - 1);

	while (bits)
	{
		if (bits)
			(bit & n) ? putchar('1') : putchar('0');
		bit >>= 1;
		--bits;
	}
	putchar('\n');
}
