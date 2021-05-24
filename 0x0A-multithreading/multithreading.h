#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <pthread.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdint.h>

#include "list.h"

#ifndef DEBUG
#define RELEASE 1
#endif

#define RED	"\033[0;31m"
#define BLUE    "\033[0;34m"
#define GREEN   "\033[0;32m"
#define GRAY    "\033[1;30m"
#define WHITE   "\033[1;37m"
#define GRAY    "\033[1;30m"
#define NC	"\033[0m"

#define FMT "%6.3f"
#define QUADCOLORS(x,y,w,h,c1,c2,c3,c4) \
	((x < w/2) ? ((y < h/2) ? c1 FMT NC : c3 FMT NC) \
		   : ((y < h/2) ? c2 FMT NC : c4 FMT NC))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ROUND(a) ((a > 0) ? (uint_fast32_t)(a + 0.5f) : (uint_fast32_t)(a - 0.5f))
#define FPTOLERANCE 0.00001f
#define EQUALISH(a, b) (((a) - FPTOLERANCE) < b && ((a) + FPTOLERANCE) > b)

/**
 * struct pixel_s - RGB pixel
 *
 * @r: Red component
 * @g: Green component
 * @b: Blue component
 */
typedef struct pixel_s
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} pixel_t;

/**
 * struct img_s - Image
 *
 * @w:      Image width
 * @h:      Image height
 * @pixels: Array of pixels
 */
typedef struct img_s
{
	size_t w;
	size_t h;
	pixel_t *pixels;
} img_t;

#define PIXEL(PIXARR) ((pixel_t){PIXARR[0], PIXARR[1], PIXARR[2]})
#define GET_PIXEL(IMG, X, Y) (IMG->pixels[ (((Y) * IMG->w) + (X)) ])
#define PUT_PIXEL(P, IMG, X, Y) (GET_PIXEL(IMG, X, Y) = PIXEL(P))

/**
 * struct kernel_s - Convolution kernel
 *
 * @size:   Size of the matrix (both width and height)
 * @matrix: Kernel matrix
 */
typedef struct kernel_s
{
	size_t size;
	float **matrix;
} kernel_t;

typedef kernel_t fakeimg_t;

/**
 * struct blur_portion_s - Information needed to blur a portion of an image
 *
 * @img:      Source image
 * @img_blur: Destination image
 * @x:        X position of the portion in the image
 * @y:        Y position of the portion in the image
 * @w:        Width of the portion
 * @h:        Height of the portion
 * @kernel:   Convolution kernel to use
 */
typedef struct blur_portion_s
{
	img_t const *img;
	img_t *img_blur;
	size_t x;
	size_t y;
	size_t w;
	size_t h;
	kernel_t const *kernel;
} blur_portion_t;

typedef void *(*task_entry_t)(void *);

/**
 * enum task_status_e - Task statuses
 *
 * @PENDING: Task is pending
 * @STARTED: Task has been started
 * @SUCCESS: Task has completed successfully
 * @FAILURE: Task has completed with issues
 */
typedef enum task_status_e
{
	PENDING = 0,
	STARTED,
	SUCCESS,
	FAILURE
} task_status_t;

/**
 * struct task_s - Executable task structure
 *
 * @entry:  Pointer to a function to serve as the task entry
 * @param:  Address to a custom content to be passed to the entry function
 * @status: Task status, default to PENDING
 * @result: Stores the return value of the entry function
 * @lock:   Task mutex
 */
typedef struct task_s
{
	task_entry_t entry;
	void *param;
	task_status_t status;
	void *result;
	pthread_mutex_t lock;
} task_t;

void *thread_entry(void *arg);
int tprintf(char const *format, ...);
void blur_portion(blur_portion_t const *portion);
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel);
list_t *prime_factors(char const *s);
task_t *create_task(task_entry_t entry, void *param);
void destroy_task(task_t *task);
void *exec_tasks(list_t const *tasks);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#ifndef C99
#define C99(...)                \
do {                        \
_Pragma("GCC diagnostic push")          \
_Pragma("GCC diagnostic ignored \"-Wpedantic\"")\
_Pragma("GCC diagnostic ignored \"-Wvla\"") \
    __VA_ARGS__             \
_Pragma("GCC diagnostic pop")           \
} while (0)
#endif /* C99 */

#ifndef DBG
#if !RELEASE
#include <stdio.h>
#define DBG(...)            \
C99(do {                \
printf("%s:%d: ", __func__, __LINE__);  \
    __VA_ARGS__;            \
} while (0);)
#else
#define DBG(...)
#endif
#endif

#pragma GCC diagnostic pop

#endif /* MULTITHREADING_H */
