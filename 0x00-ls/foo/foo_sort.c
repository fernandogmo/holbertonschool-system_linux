#include "../hls.h"

/**
 * swap - swaps two file_t pointers in an array
 * @a: pointer to first file_t pointer to swap
 * @b: pointer to second file_t pointer to swap
 *
 * Return: void
 */
void swap(file_t **a, file_t **b)
{
	file_t *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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
		if (_strcoll(array[j]->path, pivot->path) < 0)
		{
			/* dbg_swap(&array[i++], &array[j], array, hi + 1); */
			swap(&array[i++], &array[j]);
		}
	/* dbg_swap(&array[i], &array[hi], array, hi + 1); */
	swap(&array[i], &array[hi]);
	return (i);
}

/**
 * _quicksort - sorts an array of file_t pointers using partition-exchange
 * *            sorting and a bespoke comparing function in the partition call
 * @array: file_t array to be sorted
 * @size: length of @array
 */
void _quicksort(file_t **array, size_t size)
{
	if (size > 1)
	{
		int pivot = partition(array, 0, size - 1);

		_quicksort(array, pivot);
		_quicksort(array + pivot + 1, size - pivot - 1);
	}
}

/**
 * _alphasort - sorts an array of file_t pointers using partition-exchange
 * *            sorting and a bespoke comparing function in the partition call
 * @files: file_t array to be sorted
 * @file_count: length of @array
 */
void _alphasort(file_t **files, int file_count)
{
	/* TODO consider options */
	_quicksort(files, (size_t)file_count);
}

/**
 * sort_subentries - sorts an array of file_t pointers using partition-exchange
 * *            sorting and a bespoke comparing function in the partition call
 * @dirs: file_t array to be sorted
 * @dir_count: length of @array
 */
void sort_subentries(file_t **dirs, int dir_count)
{
	/* TODO consider options */
	_alphasort(dirs, (size_t)dir_count);
}
