#include <stdio.h>
#include <stdlib.h>
#include "multithreading.h"

void print_kernel(kernel_t const *k)
{
	size_t kw = k->size;
	size_t kh = k->size;
	size_t kx, ky;
	for (ky = 0; ky < kh; ky++)
	{
		for (kx = 0; kx < kw; kx++)
		{
			char *fmt = QUADCOLORS(kx,ky,kw,kh,RED,BLUE,GREEN,WHITE);
			printf(fmt, k->matrix[ky][kx]);
			putchar((kx == kw - 1) ? '\n' : ' ');
		}
	}
	putchar('\n');
}

void make_fakeimg(fakeimg_t *img, size_t size)
{
	img->size = size;
	size_t iw = img->size;
	size_t ih = img->size;
	float **m = malloc(ih * sizeof(*m));
	float count = 0.0f;
	size_t ix, iy;
	for (iy = 0; iy < ih; iy++)
	{
		m[iy] = malloc(iw * sizeof(**m));
		for (ix = 0; ix < iw; ix++)
		{
			m[iy][ix] = (count += 0.01f);
			m[iy][ix] += (ix < iw/2) ? ((iy < ih/2) ? 2.0f : 7.0f)
						: ((iy < ih/2) ? 3.0f : 5.0f);
		}
	}
	img->matrix = &m[0];
}

static inline void print_fakeimg(fakeimg_t *img)
{
	print_kernel((kernel_t *)img);
}

void copy_fakeimg(fakeimg_t *dst, fakeimg_t const *src)
{
	dst->size = src->size;
	size_t iw = dst->size;
	size_t ih = dst->size;
	float **buf = malloc(ih * sizeof(*buf));
	size_t ix, iy;
	for (iy = 0; iy < ih; iy++)
	{
		buf[iy] = malloc(iw * sizeof(**buf));
		for (ix = 0; ix < iw; ix++)
			buf[iy][ix] = src->matrix[iy][ix];
	}
	dst->matrix = &buf[0];
}

void print_fakeimg_diff(fakeimg_t *orig, fakeimg_t *this)
{
	size_t iw = orig->size;
	size_t ih = orig->size;
	size_t ix, iy;
	for (iy = 0; iy < ih; iy++)
	{
		for (ix = 0; ix < iw; ix++)
		{
			float val = this->matrix[iy][ix];
			char *fmt = EQUALISH(val, orig->matrix[iy][ix])
				? QUADCOLORS(ix,iy,iw,ih,RED,BLUE,GREEN,WHITE)
				: GRAY FMT NC;
			printf(fmt, val);
			putchar((ix == iw - 1) ? '\n' : ' ');
		}
	}
	putchar('\n');
}

void apply_kernel(ssize_t x, ssize_t y, ssize_t iw, ssize_t ih, kernel_t *k, fakeimg_t *src, fakeimg_t *dst)
{
	ssize_t kw = k->size;
	ssize_t kh = k->size;
	ssize_t ix, iy, kx, ky, r = k->size/2;
	// size_t divisor = 1;
	for (iy = y; iy < y + ih; iy++)
	{
		for (ix = x; ix < x + iw; ix++)
		{
	// if (((iy < y+2) && (ix < x+2)) || ((iy > y+ih-2) && (ix > x+iw-2)))
	// 	printf("PIXEL"FMT"\n", src->matrix[iy][ix]);
			float sum = k->matrix[r][r];
			for (ky = -r; ky < kh - r; ky++)
			{
				for (kx = -r; kx < kw - r; kx++)
				{
					float pixel = src->matrix[iy+ky][ix+kx];
					float weight = k->matrix[ky+r][kx+r];
	// if (((iy < y+2) && (ix < x+2)) || ((iy > y+ih-2) && (ix > x+iw-2)))
	// 	printf(" p ="GRAY FMT NC", k ="GRAY FMT NC"%c", pixel, weight, (kx == kw - r - 1) ? '\n' : ' ');
					dst->matrix[iy][ix] += weight * pixel;
					sum += weight;
				}
			}
			dst->matrix[iy][ix] /= sum;
		}
	}
}

void blur_portion(blur_portion_t const *portion)
{
	kernel_t k = *portion->kernel;
	puts("PRINTING KERNEL");
	print_kernel(&k);

	fakeimg_t img;
	make_fakeimg(&img, portion->img->h);
	puts("PRINTING ORIGINAL IMAGE");
	print_fakeimg(&img);

	fakeimg_t img_blur;
	copy_fakeimg(&img_blur, &img);
	puts("PRINTING BLURRING IMAGE");
	print_fakeimg(&img_blur);

	/* apply kernel to "image" */
	ssize_t iw = portion->w;
	ssize_t ih = portion->h;
	ssize_t x = portion->x;
	ssize_t y = portion->y;
	printf("BLURRING IMAGE FROM x = %ld, y = %ld\n", x, y);
	apply_kernel(x, y, iw, ih, &k, &img, &img_blur);

	puts("PRINTING BLURRED IMAGE");
	print_fakeimg_diff(&img, &img_blur);

	puts("PRINTING ORIGINAL IMAGE");
	print_fakeimg(&img);
}
