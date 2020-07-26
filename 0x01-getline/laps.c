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
			/* check if car was in race already */
			if (laps[id[i]] == 0)
			{
				printf("Car %d joined the race\n", id[i]);
				laps[id[i]] = -1;
			}
			else
			{
				/* increase laps for cars in id array */
				laps[id[i]] += (laps[id[i]] < 0) ? 2 : 1;
			}
		}

		/* print laps for all cars in race */
		printf("Race state:\n");
		for (i = 0; i < POSSIBLE_CARS; ++i)
		{
			if (laps[i] != 0)
			{
				int nlaps = (laps[i] < 0) ? 0 : laps[i];

				printf("Car %lu [%d laps]\n", i, nlaps);
			}
		}
	}
}
