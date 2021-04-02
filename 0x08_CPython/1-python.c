#include <Python.h>
#include <object.h>
#include <listobject.h>

#define PyListCast(op) ((PyListObject *)(op))

/**
 * print_python_list - prints info about python list object
 * @p: Python generic object
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t i, size;

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
		printf("Element %ld: %s\n", i,
		       Py_TYPE(PyList_GET_ITEM(p, i))->tp_name);
	}
}
