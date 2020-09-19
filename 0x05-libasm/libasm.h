#ifndef LIBASM_H
#define LIBASM_H 1

size_t asm_strlen(const char *str);
int asm_strcmp(const char *s1, const char *s2);
int asm_strncmp(const char *s1, const char *s2, size_t n);
char *asm_strchr(const char *s, int c);
char *asm_strstr(const char *haystack, const char *needle);
void *asm_memcpy(void *dest, const void *src, size_t n);
size_t asm_putc(int c);
size_t asm_puts(const char *str);
int asm_strcasecmp(const char *s1, const char *s2);
int asm_strncasecmp(const char *s1, const char *s2, size_t n);
size_t asm_strspn(const char *s, const char *accept);
size_t asm_strcspn(const char *s, const char *reject);
char *asm_strpbrk(const char *s, const char *accept);

#define TEST2(libfn, myfn, case) \
	do { \
	printf(#libfn "(\"%s\", \"%s\") \n=> %d\n", case, libfn(case));\
	printf(#myfn "(\"%s\", \"%s\") \n=> %d\n\n", case, myfn(case));\
	assert(libfn(case) == myfn(case)); \
	} while (0)

#define TEST3(libfn, myfn, case) \
	do { \
	printf(#libfn "(\"%s\", \"%s\", %d) \n=> %d\n", case, libfn(case));\
	printf(#myfn "(\"%s\", \"%s\", %d) \n=> %d\n\n", case, myfn(case));\
	assert(libfn(case) == myfn(case)); \
	} while (0)

#endif /* LIBASM_H */
