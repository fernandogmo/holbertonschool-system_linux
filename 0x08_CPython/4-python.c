#include <Python.h>

/**
 * print_python_string - print basic information about Python string objects
 * @p: pointer to PyObject
 */
void print_python_string(PyObject *p)
{
	puts("[.] string object info");
	if (PyUnicode_Check(p))
	{
		const char *type = "compact ascii"
				       ? (PyUnicode_IS_COMPACT_ASCII(p))
				       : "compact unicode object";
		wchar_t *w = PyUnicode_AsWideCharString(p, NULL);
		printf("  type: %s\n", type);
		printf("  length: %li\n", PyUnicode_GET_LENGTH(p));
		printf("  value: %ls\n", w);
		PyMem_Free(w);
	}
	else
		puts("  [ERROR] Invalid String Object");
}
