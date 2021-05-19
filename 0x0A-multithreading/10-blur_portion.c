#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "multithreading.h"

/** put_pixel - desc
 * @img: img
 * @x: x
 * @y: y
 * @rgb: rgb
 */
static inline void put_pixel(img_t *img, size_t x, size_t y, uint8_t *rgb)
{
	// uint8_t i;
	// uint8_t channels[3];
	// for (i = 0; i < 3; i++)
	// 	channels[i] = (float)ROUND(rgb[i]);
	// pixel_t px = (pixel_t){channels[0], channels[1], channels[2]};
	// for (i = 0; i < 3; i++)
	// 	rgb[i] = (float)ROUND(rgb[i]);
	pixel_t px = (pixel_t){rgb[0], rgb[1], rgb[2]};
	size_t offset = (y * img->w) + x;
	img->pixels[offset] = px;
}

/**
 * get_pixel - desc
 * @img: img
 * @x: x
 * @y: y
 * @n: n
 * Return: uint8_t
 */
static inline uint8_t get_pixel(const img_t *img, ssize_t x, ssize_t y, size_t n)
{
	size_t offset = (y * img->w) + x;
	pixel_t px = img->pixels[offset];
	uint8_t pxs[3] = {px.r, px.g, px.b};
	return ((n < 3) ? pxs[n] : 1);
}

/**
 * blur_portion - desc
 * @portion: portion
 */
void blur_portion(blur_portion_t const *portion)
{
	const kernel_t *k = portion->kernel;
	const img_t *src = portion->img;
	img_t *dst = portion->img_blur;
	ssize_t x = portion->x, y = portion->y;
	ssize_t iw = portion->w, ih = portion->h;
	ssize_t kw = k->size, kh = k->size;
	ssize_t ix, iy, kx, ky, n, r = k->size/2;
	for (iy = y; iy < y + ih; iy++)
	{
		for (ix = x; ix < x + iw; ix++)
		{
			float sum = k->matrix[r][r], rgb_floats[3] = {0.0f};
			// float sum = 0.0f, rgb[3] = {0.0f};
			for (n = 0; n < 3; n++) rgb_floats[n] = get_pixel(dst, ix, iy, n);
#define IN_REGION_ONE ((iy < y+1) && (ix < x+1))
#define IN_REGION_TWO ((iy > y+ih-2) && (ix < x+1))
#define IN_REGION_THREE ((iy > y+ih-2) && (ix > x+iw-2))
#define IN_REGIONS_ONE_OR_TWO ( IN_REGION_ONE || IN_REGION_TWO)
#define IN_REGIONS_ONE_OR_THREE ( IN_REGION_ONE || IN_REGION_THREE)
#define IN_REGION_OF_INTEREST IN_REGIONS_ONE_OR_TWO
if IN_REGION_OF_INTEREST
{
	printf("DST PIXEL ");
	for (n = 0; n < 3; n++)
		printf(FMT"%c", rgb_floats[n], (n == 2) ? '\n' : ' ');
		// printf(FMT"%c", (float)get_pixel(dst, ix, iy, n), (n == 2) ? '\n' : ' ');
}
			for (ky = -r; ky < kh - r; ky++)
			{
				for (kx = -r; kx < kw - r; kx++)
				{
					// if ((ix + kx >= 0 && (size_t)(ix + kx) < src->w) &&
					//     (iy + ky >= 0 && (size_t)(iy + ky) < src->h))
					{
						float wgt = k->matrix[ky+r][kx+r];
						for (n = 0; n < 3; n++)
							rgb_floats[n] += wgt * get_pixel(src, ix + kx, iy + ky, n);
						sum += wgt;
					}
				}
			}
if IN_REGION_OF_INTEREST
{
	printf("PRE PIXEL ");
	for (n = 0; n < 3; n++)
		printf(FMT"%c", rgb_floats[n], (n == 2) ? '\n' : ' ');
		// printf(FMT"%c", (float)get_pixel(dst, ix, iy, n), (n == 2) ? '\n' : ' ');
}
			for (n = 0; n < 3; rgb_floats[n++] /= sum);
			// for (n = 0; n < 3; n++) rgb_floats[n] = MIN(rgb_floats[n], 255.0);
			// for (n = 0; n < 3; n++) rgb_floats[n] = MAX(rgb_floats[n], 0.0);
if IN_REGION_OF_INTEREST
{
	printf("NEW PIXEL ");
	for (n = 0; n < 3; n++)
		printf(FMT"%c", rgb_floats[n], (n == 2) ? '\n' : ' ');
		// printf(FMT"%c", (float)get_pixel(dst, ix, iy, n), (n == 2) ? '\n' : ' ');
}
			uint8_t rgb[3] = {0};
			for (n = 0; n < 3; n++)
				rgb[n] = (float)ROUND(rgb_floats[n]);
			put_pixel(dst, ix, iy, rgb);
if IN_REGION_OF_INTEREST
{
	printf("END PIXEL ");
	for (n = 0; n < 3; n++)
		// printf(FMT"%c", rgb[n], (n == 2) ? '\n' : ' ');
		printf(FMT"%c", (float)get_pixel(dst, ix, iy, n), (n == 2) ? '\n' : ' ');
	printf("\n");
}
		}
	}
}
