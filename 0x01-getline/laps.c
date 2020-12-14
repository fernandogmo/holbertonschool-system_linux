#include "laps.h"

#define POSSIBLE_CARS 255
static int laps[POSSIBLE_CARS];

/**
 * race_state - updates race state and reports to stdout
 * @id: array of unique integer IDs for cars
 * @size: length @id
 */
void race_state(int *id, size_t size)
{
	if (id != NULL)
	{
		size_t i;

		for (i = 0; i < size; ++i)
		{
			/* if a car's lap count is zero then it hasn't joined the race */
			if (laps[id[i]] == 0)
			{
				printf("Car %d joined the race\n", id[i]);
				/* lap count value of -1 means the car is on it's first lap */
				laps[id[i]] = -1;
			}
			else
			{
				/**
				 * increase completed lap count for cars in id array
				 * if on 1st lap (-1), inc by 2 to set to 1 completed lap
				 * otherwise increment lap count by 1
				 */
				laps[id[i]] += (laps[id[i]] < 0) ? 2 : 1;
			}
		}

		/* print laps for all cars in race */
		printf("Race state:\n");
		for (i = 0; i < POSSIBLE_CARS; ++i)
		{
			if (laps[i] != 0)
			{
				/**
				 * -1 means 0 laps completed
				 * otherwise use value recorded at index == id
				 */
				int nlaps = (laps[i] < 0) ? 0 : laps[i];

				printf("Car %lu [%d laps]\n", i, nlaps);
			}
		}
	}
}
