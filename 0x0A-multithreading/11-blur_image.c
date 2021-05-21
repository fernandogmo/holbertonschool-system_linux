#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "multithreading.h"

#define NUMTHREADS 4

void *_thread_entry(void *arg)
{
	blur_portion((const blur_portion_t *)arg);
	return (NULL);
}

void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{C99(
	pthread_t thr[NUMTHREADS];
	blur_portion_t ptn[NUMTHREADS];
	size_t i;
	for (i = 0; i < NUMTHREADS; i++)
		ptn[i] = (blur_portion_t){img, img_blur, 0, 0, 0, 0, kernel};

	for (i = 0; i < NUMTHREADS; i++)
	{
		ptn[i].w = ptn[i].img->w / 2;
		ptn[i].h = ptn[i].img->h / 2;
		/* printf("(%lu, %lu)\n", (i % 2), ((i/2) % 2)); */
		ptn[i].x = ptn[i].w * (i % 2);
		ptn[i].y = ptn[i].h * ((i/2) % 2);
		pthread_create(&thr[i], NULL, &_thread_entry, &ptn[i]);
	}
	for (i = 0; i < NUMTHREADS; i++)
		pthread_join(thr[i], NULL);
);}
