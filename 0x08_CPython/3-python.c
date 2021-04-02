#include <Python.h>

/**
 * print_python_list - print basic info about Python list objects
 * @p: pointer to PyObject
 */
void print_python_list(PyObject *p)
{
	setbuf(stdout, NULL);
	puts("[*] Python list info");
	if (PyList_Check(p))
	{
		Py_ssize_t size = PyList_GET_SIZE(p);
		printf("[*] Size of the Python List = %li\n", size);
		printf("[*] Allocated = %li\n", ((PyListObject *)p)->allocated);
		for (Py_ssize_t i = 0; i < size; ++i)
		{
			PyObject *item = PyList_GET_ITEM(p, i);
			printf("Element %li: %s\n", i, item->ob_type->tp_name);
			if (PyBytes_Check(item))
				print_python_bytes(item);
			else if (PyFloat_Check(item))
				print_python_float(item);
		}
	}
	else
		puts("  [ERROR] Invalid List Object");
}

/**
 * print_python_bytes - print basic info about Python byte objects
 * @p: pointer to PyObject
 */
void print_python_bytes(PyObject *p)
{
	setbuf(stdout, NULL);
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
 * print_python_float - print basic info about Python float objects
 * @p: pointer to PyObject
 */
void print_python_float(PyObject *p)
{
	setbuf(stdout, NULL);
	puts("[.] float object info");
	if (PyFloat_Check(p))
	{
		char *s = PyOS_double_to_string(PyFloat_AsDouble(p), 'r', 0,
						Py_DTSF_ADD_DOT_0, NULL);
		printf("  value: %s\n", s);
		PyMem_Free(s);
	}
	else
		puts("  [ERROR] Invalid Float Object");
}
