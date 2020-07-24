#include "../hls.h"

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int _strcoll(char *s1, char *s2)
{
	return (_strcmp(s1, s2));
}

/**
 * _swap - swaps two file_t pointers in an array
 * @a: pointer to first file_t pointer to swap
 * @b: pointer to second file_t pointer to swap
 *
 * Return: void
 */
void _swap(file_t **a, file_t **b)
{
	file_t *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * print_array - Prints pathnames in an array of file_t pointers
 *
 * @array: The array to be printed
 * @size: Number of elements in @array
 */
void print_array(file_t **array, size_t size)
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
 * dbg_swap - swaps two values in file_t pointer array if they are not equal, and
 *        prints the current state of the array it was first called with.
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
		print_array(ptr, s);
	}
}

/**
 * partition - implements Lomuto partitioning scheme
 * *           for an array of file_t pointers
 * @array: array of file_t pointers to partition
 * @lo: low index
 * @hi: high index for pivot
 * Return: index of partition
 */
int partition(file_t **array, int lo, int hi)
{
	int i, j;
	file_t *pivot = array[hi];

	for (j = i = lo; j < hi; j++)
		/* if (array[j] < pivot) */
		if (_strcoll(array[j]->path, pivot->path) == -1)
		{
			/* dbg_swap(&array[i++], &array[j], array, hi + 1); */
			swap(&array[i++], &array[j]);
		}
	/* dbg_swap(&array[i], &array[hi], array, hi + 1); */
	swap(&array[i], &array[hi]);
	return (i);
}

/**
 * quick_sort - sorts an array of file_t pointers using partition-exchange
 * *            sorting and a bespoke comparing function in the partition call
 * @array: file_t array to be sorted
 * @size: length of @array
 */
void quick_sort(file_t **array, size_t size)
{
	if (size > 1)
	{
		int pivot = partition(array, 0, size - 1);

		quick_sort(array, pivot);
		quick_sort(array + pivot + 1, size - pivot - 1);
	}
}
