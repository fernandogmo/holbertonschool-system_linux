#include <Python.h>

/**
 * print_python_bytes - prints info about python bytes object
 * @p: pointer to PyObject
 */
void print_python_bytes(PyObject *p)
{
	puts("[.] bytes object info");
	if (PyBytes_Check(p))
	{
		Py_ssize_t size = PyBytes_Size(p);
		char *str = PyBytes_AsString(p);
		printf("  size: %ld\n", size);
		printf("  trying string: %s\n", str);
		printf("  first %ld bytes:", size = size < 10 ? size + 1 : 10);
		for (Py_ssize_t i = 0; i < size; ++i)
			printf(" %02hhx", str[i]);
		putchar('\n');
	}
	else
		puts("  [ERROR] Invalid Bytes Object");
}

/**
 * print_python_list - prints info about python list object
 * @p: pointer to PyObject
 */
void print_python_list(PyObject *p)
{
	printf("[*] Python list info\n");
	if (PyList_Check(p))
	{
		Py_ssize_t size = PyList_Size(p);
		printf("[*] Size of the Python List = %ld\n", size);
		printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);
		for (Py_ssize_t i = 0; i < size; ++i)
		{
			PyObject *item = PyList_GET_ITEM(p, i);
			printf("Element %ld: %s\n", i, item->ob_type->tp_name);
			if (PyBytes_Check(item))
				print_python_bytes(item);
		}
	}
	else
		puts("  [ERROR] Invalid List Object");
}
