#ifndef _LAPS_H_
#define _LAPS_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __INT_MAX__
#define INTMAX __INT_MAX__
#else
#define INTMAX ((2**32) / 2)
#endif

void race_state(int *id, size_t size);


#endif /* _LAPS_H_ */
