#include <Python.h>

#define PyListCast(op) ((PyListObject *)(op))
#define PyBytesCast(op) ((PyBytesObject *)(op))

/**
 * print_python_bytes - prints info about python bytes object
 * @p: Python generic object
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size, i;
	char *str;

	printf("[.] bytes object info\n");
	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}
	size = PyBytes_Size(p);
	str = PyBytes_AsString(p);
	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", str); /*FIXME: ???*/
	size = size + 1 > 10 ? 10 : size + 1;
	printf("  first %ld bytes:", size);
	for (i = 0; i < size; ++i)
	{
		printf(" %02hhx", str[i]);
	}
	putchar('\n');
}

/**
 * print_python_list - prints info about python list object
 * @p: Python generic object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t i, size;
	PyObject *item;

	if (!p || !PyList_Check(p))
	{
		return;
	}

	size = PyList_Size(p);
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", PyListCast(p)->allocated);
	for (i = 0; i < size; ++i)
	{
		item = PyList_GET_ITEM(p, i);
		printf("Element %ld: %s\n", i, item->ob_type->tp_name);
		if (PyBytes_Check(item))
			print_python_bytes(item);
	}
}
