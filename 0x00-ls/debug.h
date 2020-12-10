#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define dbg_printf printf

/* debug.c */
void dbg_print_binary(unsigned char);
void dbg_print_file_array(file_t **, size_t);
void dbg_swap(file_t **, file_t **, file_t **, size_t);

#else

#define dbg_printf(...)
#define dbg_print_binary(x)
#define dbg_print_file_array(x)
#define dbg_swap(x, y, s, t)

#endif /* DEBUG */

#endif /* DEBUG_H */
